#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <assert.h>
#include "k_init_struct.h"
#include "k_globals.h"
#include "k_io_buffer.c"

int main(){

	/************Initializations************/
	caddr_t mmap_ptr;
	extern k_io_buffer_ptr input_buf; 
	input_buf = k_io_buffer_init();
	char *inputfile = "inputfile";		//Naming sharedmem file	
	int RTX_pid = getpid();			//Store PID of RTX
	//Create file to map memory to
	int fid = open(inputfile, O_RDWR | O_CREAT , (mode_t) 0755);	
	assert(fid>0);
	ftruncate(fid, BUFFER_SIZE); 		//Change size of file to match buffer size
	char kbd_info[2] = {RTX_pid, fid};	//Char array required for execl function
	char c;
	int i;
	
	printf("\n\nRTX_pid = %d\n",RTX_pid);
	printf("fid = %d\n",fid);
	
	/************Forking into Keyboard Helper************/
	int newPID = fork();
	printf("child PID = %d",newPID);
	if(newPID == 0)				//Check that fork was successful
		execl("../helpers/kbd_helper", "kbd_helper",kbd_info, (char *)NULL);	
	
	/************Mapping memory to the file************/
	mmap_ptr = mmap((caddr_t) 0,			// Memory Location, 0 lets OS choose
			BUFFER_SIZE,			// How many bytes to mmap
			PROT_READ | PROT_WRITE, 	// Read and write permissions
			MAP_SHARED,    			// Accessible by another process
			fid,           			// Which file is associated with mmap
			(off_t) 0);			// Offset in page frame
	assert(mmap_ptr != MAP_FAILED);
	
	input_buf = (k_io_buffer_ptr) mmap_ptr;		//creating pointer to the sharedmem

	/************Testing helper process************/
	while(1)
	{
		if(input_buf->wait_flag == 1)
		{
			printf("User input:  ");
			for(i=0;i<input_buf->length;i++)
			{
				c = input_buf->bufdata[i];
				printf("%c",c);
			}
			printf("\n");
		}
	}

}
