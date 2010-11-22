#include <stdlib.h>
#include <stdlio.h>
#include <unistd.h>
#include <sys/mman.h>
#include "k_io_buffer.h"

/****************************************************************
 CRT Helper Process 
 ----------------------------------------------------------------
 This function emmulates the hardware interrupts for the RTX.  
 It periodically checks if the RTX has stored data in a io_buffer 
 struct.  It then prints the data to the screen.

*****************************************************************/

int crt (char *CRTbuffer[]){
	
	/************Initializations************/
	int rtx_pid, fid;		//To store RTX process id and memory mapped file id
	io_buffer *output_buf;		//Creates pointer to buffer struct	

	/************Getting IDs array pointer that was passed in************/
	sscanf(KBbuffer[0], "%d", &rtx_pid );	//Get rtx process id
	sscanf(KBbuffer[1], "%d", &fid );	//Get memory mapped file id
	
	
	/************Mapping memory to the file************/
	mmap_ptr = 	mmap((caddr_t) 0,		// Memory Location, 0 lets O/S choose
				BUFSIZE,		// How many bytes to mmap
				PROT_READ | PROT_WRITE, // Read and write permissions
				MAP_SHARED,		// Accessible by another process
				fid, 			// Which file is associated with mmap
				(off_t) 0);		// Offset in page frame
	
	output_buf = (io_buffer *) mmap_ptr		//creating pointer to the shared memory
	
	
	/************Printing to the screen************/
	while(1)					//Loop forever
	{
		kill(rtx_pid,SIGUSR2); 			//Signal the RTX		
		usleep(100000);				//Wait for RTX to add to the buffer
		if (output_buf->length > 0)
		{					//Run statements below if there is something in the buffer
			for(i=0;i<output_buf->length; i++)
				printf ("%c", output_buf->bufdata[i]);	//Print all characters in the string
			output_buf->length = 0;		//Set length back to zero
			output_buf->wait_flag = 0;
		}					//Set wait_flag back to zero
	}
}
