#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include "k_io_buffer.c"

/****************************************************************
 Keyboard Helper Process 
 ----------------------------------------------------------------
 This function emmulates the hardware interrupts for the RTX.  
 It accepts keystrokes from the user and stores the data in a 
 io_buffer struct.  It then signals the RTX that the user has 
 inputted data and waits for the buffer to clear.

*****************************************************************/

int keyboard (char *KBbuffer[]){

	/************Initializations************/
	io_buffer *input_buf;		//Creates pointer to buffer struct
	int rtx_pid, fid;		//To store RTX process id and memory mapped file id
	char c;				//Char for key being typed

	
	/************Getting IDs array pointer that was passed in************/
	sscanf(KBbuffer[0], "%d", &rtx_pid );		//Get rtx process id
	sscanf(KBbuffer[1], "%d", &fid );		//Get memory mapped file id
	
	
	/************Mapping memory to the file************/
	mmap_ptr = 	mmap((caddr_t) 0,		// Memory Location, 0 lets OS choose
				BUFFER_SIZE,		// How many bytes to mmap
				PROT_READ | PROT_WRITE, // Read and write permissions
				MAP_SHARED,    		// Accessible by another process
				fid,           		// Which file is associated with mmap
				(off_t) 0);		// Offset in page frame
	
	input_buf = (io_buffer *) mmap_ptr		//creating pointer to the shared memory
	
	
	/************Reading from the keyboard************/
	while(1)			  		//Loop forever
	{
		c = getchar();				//Get inputted character 
		input_buf->length++;
		
	/*Signal the RTX if there is a carriage return or if the string equals the size of the 		buffer.  Since BUFSIZE equals the max size of an envelope, the string should not reach 		this length anyway...	*/

	 	if (c=='\n' || input_buf->length==BUFFER_SIZE)
		{
			//Set last character to null
			input_buf->bufdata[input_buf->length-1] = '\0';		
			kill(rtx_pid,SIGUSR1);		//Signal the RTX	
			input_buf->wait_flag = 1;	//Set wait_flag to true
			while(input_buf->wait_flag == 1)
			//Check every 100 miliseconds if the RTX has cleared the flag
				usleep(100000);
		}	//(ie: it has read from the buffer)
		else
			input_buf->bufdata[input_buf->length-1] = c;
	}
}

