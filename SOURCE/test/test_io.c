#include "k_io.h"
#include "k_messages.h"
#include "k_init_struct.h"

int main()
{
	printf("TESTING I/O FUNCTIONS \n \n")
	
	printf("TESTING INPUT... \n")
	
	k_message_ptr key_in;
	key_in = NULL;
	printf("Inserting NULL Function = %d \n", get_console_chars(key_in));
	key_in = k_message_init;
	
	printf("Testing get_console_chars = %d \n", get_console_chars(key_in));
	printf("reciever_pid = %d \n", key_in->reciever_pid)
	printf("sender_pid = %d \n", key_in->sender_pid)
	printf("reciever_pid = %d \n", key_in->msg_type)
	printf("msg_size = %d \n", key_in->msg_size)
	
	printf("TESTING OUTPUT... \n")
	
	k_message_ptr crt_out;
	crt_out = NULL;
	printf("Inserting NULL Function = %d \n", send_console_chars(crt_out));
	crt_out = k_message_init;
	
	//remember to set msg to something
	printf("Testing send_console_chars = %d \n", send_console_chars(crt_out));
	printf("reciever_pid = %d \n", crt_out->reciever_pid)
	printf("sender_pid = %d \n", crt_out->sender_pid)
	printf("reciever_pid = %d \n", crt_out->msg_type)
	printf("msg_size = %d \n", crt_out->msg_size)


}
