#include "k_message.h"
#include "k_message_queue.h"
#include "test_message_queue.h"
#include "k_init_struct.h"
#include "k_ipc.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//ipc
int main()
{
	printf("TESTING IPC FUNCTIONS \n");
	int i, j;
	k_message_ptr message; 
/*	k_message_queue_ptr k_freeQ;

	freeMQ = k_message_queue_init();
	
	for (i=0; i< 3; i++)
	{
		message = k_message_init();
		message->sender_pid = 0;
		message->receiver_pid = 0;
		message->msg_type = 0;
		message->msg_size = 0;
		message->expiry_time = 0;
		k_message_queue_enqueue(message, freeMQ);
	}
*/
	printf("Testing Successfull Request\n");

	i = k_current_process->p_pid;	
	message = k_request_msg_env();

	assert(message != NULL);
	assert(i == k_current_process->p_pid);
	
	printf("---->PASS\n");
	
	printf("Testing Successfull Send\n");
	message->msg_size = 3;
	j = k_send_message(2, message);
	
	assert(j == 1);
	message = NULL;

	printf("---->PASS\n");

	printf("Testing Successfull Receive\n");
	
	while (k_current_process->p_pid != 2) {
		release_processor();
	message = k_receive_message();
	
	assert(message != NULL);
	assert(i == k_current_process->p_pid);

	printf("MESSAGE QUEUE PASSED\n");

}
