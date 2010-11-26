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
	char c;
	int i;
	caddr_t mmap_ptr;

	extern k_io_buffer_ptr k_input_buf; 
	k_input_buf = k_io_buffer_init();		//Initializing input buffer
	char *inputfile = "helpers/inputfile";		//Naming sharedmem file	
	int fid = open(inputfile, O_RDWR | O_CREAT , (mode_t) 0755);	//Create file
	assert(fid>0);
	ftruncate(fid, BUFFER_SIZE); 		//Change size of file to match buffer size

	char kbd_info1[20],kbd_info2[20];	//Arguments for execl function
	sprintf(kbd_info1, "%d", RTX_pid);
	sprintf(kbd_info2, "%d", fid);
	
	/************Forking into Keyboard Helper************/
	int newPID = fork();
	if(newPID == 0)				//Check that fork was successful
	{
		i = execl("./helpers/kbd_helper", "kbd_helper", kbd_info1, kbd_info2, (char *)0);
		printf("If here, execl failed.  execl = %d\n",i);
	}

	/************Mapping memory to the file************/
	mmap_ptr = mmap((caddr_t) 0,		// Memory Location, 0 lets OS choose
			BUFFER_SIZE,		// How many bytes to mmap
			PROT_READ | PROT_WRITE, // Read and write permissions
			MAP_SHARED,    		// Accessible by another process
			fid,           		// Which file is associated with mmap
			(off_t) 0);		// Offset in page frame
	assert(mmap_ptr != MAP_FAILED);
	
	k_input_buf = (k_io_buffer_ptr) mmap_ptr;		//Creating pointer to the sharedmem

	/************Testing helper process************/
	while(1)
	{
		if(k_input_buf->wait_flag == 1)			//While buffer is nonempty
		{
			printf("User input:  ");		
			for(i=0;i<k_input_buf->length;i++)	 
			{
				c = k_input_buf->bufdata[i];	
				printf("%c",c);		
			}
			printf("\n");
			k_input_buf->wait_flag = 0;
			k_input_buf->length = 0;
		}
	}

}
