#include "k_message.h"
#include "k_message_queue.h"
#include "test_message_queue.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("Starting \n");
	int i, j;

	 printf("TESTING MESSAGE QUEUE\n\n");

	// Initializing queue
	k_message_queue_ptr MQ = malloc(sizeof(k_message_queue));

	test_message_queue_print(MQ);
	printf("queue_is_empty = %d \n", k_message_queue_is_empty(MQ));
	printf("Start Enqueue \n");
	test_message_queue_print(MQ);
	for (i=0; i< 10; i++)
	{
		MsgEnv_ptr message = malloc(sizeof(MsgEnv));
		message->sender_pid = i+1;
		k_message_queue_enqueue(message, MQ);
		test_message_queue_print(MQ);
		printf("\n\n");
	}
	printf("Done Enqueue\n\n");
	printf("Start Dequeue\n");

	for (i=0; i< 10; i++)
	{
		MsgEnv_ptr message;
		message = k_message_queue_dequeue(MQ);
		printf("Dequeued MESSAGE = %d || Next = %p\n", message->sender_pid,message->k_queue_next);
		test_message_queue_print(MQ);
		printf("\n\n");
	}
	printf("Done Dequeue\n\n");

	printf("Test dequeue Empty Queue\n");
	
	MsgEnv_ptr message;
	message = k_message_queue_dequeue(MQ);	
	if(message == NULL);
		printf("PASSED \n");
	message = k_message_queue_dequeue(MQ);
	test_message_queue_print(MQ);
	printf("\n\n");	
	printf("DONE\n");
}
