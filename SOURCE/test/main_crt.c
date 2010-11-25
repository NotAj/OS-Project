#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <assert.h>
#include "k_init_struct.h"
#include "k_globals.h"
#include "k_io_buffer.c"
#include "k_defines.h"

int main(){

	/************Initializations************/
	int RTX_pid = getpid();			//Store PID of RTX
	int i;
	char c;
	caddr_t mmap_ptr;

	extern k_io_buffer_ptr output_buf;
	output_buf = k_io_buffer_init();	//Initializing output buffer
	char *outputfile = "outputfile";	//Naming sharedmem file	
	int fid = open(outputfile, O_RDWR | O_CREAT, (mode_t) 0755);	//Create file 
	assert(fid>0);
	ftruncate(fid, BUFFER_SIZE); 		//Change size of file to match buffer size

	char crt_info1[20], crt_info2[20];	//Arguments for execl function
	sprintf(crt_info1, "%d", RTX_pid);
	sprintf(crt_info2, "%d", fid);

	printf("\n\nCHECKS:\n");
	printf("IN RTOS: RTX_pid = %d\n",RTX_pid);
	printf("IN RTOS: fid = %d\n",fid);
	
	/************Forking into CRT Helper************/
	int newPID = fork();
	if(newPID == 0)				//Check that fork was successful
	{
		i = execl("./helpers/crt_helper", "crt_helper",crt_info1, crt_info2, (char *)NULL);	
		printf("If here, execl failed.  execl = %d\n",i);
	}

	/************Mapping memory to the file************/
	mmap_ptr = mmap((caddr_t) 0,			// Memory Location, 0 lets OS choose
			BUFFER_SIZE,			// How many bytes to mmap
			PROT_READ | PROT_WRITE, 	// Read and write permissions
			MAP_SHARED,    			// Accessible by another process
			fid,           			// Which file is associated with mmap
			(off_t) 0);			// Offset in page frame
	assert(mmap_ptr != MAP_FAILED);
	
	output_buf = (k_io_buffer_ptr) mmap_ptr;	//creating pointer to the sharedmem

	/************Testing helper process************/
	while(1)			  		//Loop forever
	{
		c = getchar();					//Get outputted character 
		output_buf->length += 1;
	 	if (c=='\n' || output_buf->length==BUFFER_SIZE)
		{
			//Set last character to null
			output_buf->bufdata[output_buf->length-1] = '\0';		
//			kill(rtx_pid,SIGUSR1);		//Signal the RTX	
			output_buf->wait_flag = 1;	//Set wait_flag to true
			while(output_buf->wait_flag == 1)
			//Check every 100 miliseconds if the RTX has cleared the flag
				usleep(10000);
		}	//(ie: it has read from the buffer)
		else
		{
			output_buf->bufdata[output_buf->length-1] = c;
		}
	}	
}
