#include "k_io.h"
#include "k_message.h"
#include "k_globals.h"
#include "k_defines.h"
#include "k_init_struct.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
	printf("TESTING I/O FUNCTIONS \n \n");
	
	extern k_PCB_ptr k_current_process;
	k_current_process = k_PCB_init(2,0,0,NULL);

	printf("TESTING INPUT... \n");

	k_message_ptr key_in;
	key_in = NULL;
	printf("Inserting NULL Function = %d \n", get_console_chars(key_in));
	key_in = k_message_init();
	
	printf("Testing get_console_chars = %d \n", get_console_chars(key_in));
	printf("reciever_pid = %d \n", key_in->receiver_pid);
	printf("sender_pid = %d \n", key_in->sender_pid);
	printf("msg_type = %d \n", key_in->msg_type);
	printf("msg_size = %d \n", key_in->msg_size);
	
	printf("TESTING OUTPUT... \n");
	
	k_message_ptr crt_out;
	crt_out = NULL;
	printf("Inserting NULL Function = %d \n", send_console_chars(crt_out));
	crt_out = k_message_init();
	
	int i;	
	for (i=0;i<=19;i++)
	{
		crt_out->msg_text[i] = 'a';
		printf("%c \n", crt_out->msg_text[i]);
	}
	crt_out->msg_text[20] = '\0';

	printf("Testing send_console_chars = %d \n", send_console_chars(crt_out));
	printf("reciever_pid = %d \n", crt_out->receiver_pid);
	printf("sender_pid = %d \n", crt_out->sender_pid);
	printf("msg_type = %d \n", crt_out->msg_type);
	printf("msg_size = %d \n", crt_out->msg_size);

	for (i=0;i<=10;i++)
	{
		crt_out->msg_text[i] = 'a';
		printf("%c \n", crt_out->msg_text[i]);
	}
	crt_out->msg_text[11] = '\0';
	send_console_chars(crt_out);
	printf("msg_size = %d \n", crt_out->msg_size);
}
