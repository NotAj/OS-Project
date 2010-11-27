#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <signal.h>
#include <assert.h>
#include "k_io_buffer.c"
#include "k_defines.h"

/****************************************************************
 CRT Helper Process 
 ----------------------------------------------------------------
 This function emmulates the hardware interrupts for the RTX.  
 It periodically checks if the RTX has stored data in a io_buffer 
 struct.  It then prints the data to the screen.

*****************************************************************/

int main (int argc, char *CRTbuffer[]){
	
	/************Initializations************/
	caddr_t mmap_ptr;
	k_io_buffer_ptr output_buf;	//Creates an io_buffer pointer 
	int rtx_pid, fid;		//To store RTX process id and memory mapped file id
	int i;

	/************Getting IDs array pointer that was passed in************/
	sscanf(CRTbuffer[1], "%d", &rtx_pid );		//Get rtx process id
	sscanf(CRTbuffer[2], "%d", &fid );		//Get memory mapped file id
		
	/************Mapping memory to the file************/
	mmap_ptr = 	mmap((caddr_t) 0,	// Memory Location, 0 lets O/S choose
			BUFFER_SIZE,		// How many bytes to mmap
			PROT_READ | PROT_WRITE, // Read and write permissions
			MAP_SHARED,		// Accessible by another process
			fid, 			// Which file is associated with mmap
			(off_t) 0);		// Offset in page frame
	assert(mmap_ptr != MAP_FAILED);

	output_buf = (k_io_buffer_ptr) mmap_ptr;	//creating pointer to the shared memory
	output_buf->length = 0;
	output_buf->wait_flag = 0;
	
	/************Printing to the screen************/
	while(1)					//Loop forever
	{
		kill(rtx_pid,SIGUSR2); 			//Signal the RTX		
		usleep(100000);				//Wait for RTX to add to the buffer
		if (output_buf->wait_flag == 0)		
		// If helper is ready to run and buffer not empty
		// (Fix for random newlines if helper not killed)
		{
			for(i=0;i<output_buf->length; i++)
				printf ("%c", output_buf->bufdata[i]);	//Print all chars 
			//printf("%s", output_buf->bufdata);
			output_buf->length = 0;		//Set length back to zero
			output_buf->wait_flag = 1;	//Set wait_flag back to 1
		}				
	}
}
