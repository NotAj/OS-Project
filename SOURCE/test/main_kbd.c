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

int main()
{

	extern k_io_buffer_ptr k_input_buf;
	char c;
	int i;

	k_global_init();		
	k_helper_init();
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
