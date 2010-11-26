#include "k_message.h"
#include "k_timeout_queue.h"
#include "test_timeout_queue.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("Starting \n");
	int i;

	 printf("TESTING TIMEOUT QUEUE\n\n");

	// Initializing queue
	k_timeout_queue_ptr TQ = malloc(sizeof(k_timeout_queue));

	printf("Start Enqueue \n");
	test_timeout_queue_print(TQ);
	for (i=0; i< 5; i++)
	{
		k_message_ptr message = malloc(sizeof(k_message));
		message->expiry_time = (i*10) + 10;
		printf("%d \n", i);
		k_timeout_queue_enqueue(message, TQ);
		test_timeout_queue_print(TQ);
		printf("\n\n");
	}
	
	k_message_ptr message = malloc(sizeof(k_message));
	message->expiry_time = 30;
	k_timeout_queue_enqueue(message, TQ);
	test_timeout_queue_print(TQ);
	
	k_message_ptr message2 = malloc(sizeof(k_message));
	message2->expiry_time = 0;
	k_timeout_queue_enqueue(message2, TQ);
	test_timeout_queue_print(TQ);

	printf("Done Enqueue\n\n");

	printf("Start Dequeue\n");

	message = k_timeout_queue_dequeue(TQ);
	printf("Dequeued MESSAGE expiry time = %d \n", message->expiry_time);
	test_timeout_queue_print(TQ);
	
	printf("\n\n");

	printf("Done Dequeue\n\n");

	printf("Test dequeue with no 0 entries \n");
	
	message = k_timeout_queue_dequeue(TQ);	
	if(message == NULL);
		printf("PASSED \n");
	message = k_timeout_queue_dequeue(TQ);
	test_timeout_queue_print(TQ);
	printf("\n\n");	
	printf("DONE\n");
}
