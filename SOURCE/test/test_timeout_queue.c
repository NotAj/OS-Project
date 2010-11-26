#include "test_timeout_queue.h"
#include <stdlib.h>
#include <stdio.h>

void test_timeout_queue_print(k_timeout_queue_ptr TQ)
{
	int i = 0;
	k_message_ptr curr_message = NULL;
	if (TQ->head == NULL)
	{	
		printf("Empty Queue \n\n");
		return;
	}
	printf("**TIMEOUT QUEUE**\n");
	curr_message = TQ->head;	
	printf("Item %d = %d \n", i, curr_message->expiry_time);
	i++;	
	while (curr_message->k_queue_next != NULL)
	{
		curr_message = curr_message->k_queue_next;
		printf("Item %d = %d \n", i, curr_message->expiry_time);
		i++;
	}
	printf("\n");
}
