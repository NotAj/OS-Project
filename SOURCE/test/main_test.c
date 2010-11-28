#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <assert.h>
#include "k_init.h"
#include "k_init_struct.h"
#include "k_globals.h"
#include "k_io_buffer.c"
#include "k_defines.h"

int main()
{
	extern k_io_buffer_ptr k_output_buf;
	char c;
	int i;

	k_global_init();		
	k_helper_init();
k_init();
	/************Testing helper process************/
/*	while(1)			  		//Loop forever
	{
		c = getchar();					//Get outputted character 
		k_output_buf->length += 1;
	 	if (c=='\n' || k_output_buf->length==BUFFER_SIZE)
		{
			//Set last character to null
			k_output_buf->bufdata[k_output_buf->length-1] = '\0';		
			k_output_buf->wait_flag = 1;	//Set wait_flag to true
			while(k_output_buf->wait_flag == 1)
			//Check every 100 miliseconds if the RTX has cleared the flag
				usleep(10000);
		}	//(ie: it has read from the buffer)
		else
		{
			k_output_buf->bufdata[k_output_buf->length-1] = c;
		}
	}	*/
}
