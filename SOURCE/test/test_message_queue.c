#include "test_message_queue.h"
#include <stdlib.h>
#include <stdio.h>

void test_message_queue_print(k_message_queue_ptr MQ)
{
	int i = 0;
	k_message_ptr curr_message = NULL;
	if (k_message_queue_is_empty(MQ))
	{	
		printf("Empty Queue \n\n");
		return;
	}
	printf("**PRIORITY QUEUE**\n");
	curr_message = MQ->head;	
	printf("Item %d = %d || Next = %p \n", i, curr_message->sender_pid, curr_message->k_queue_next);
	i++;	
	while (curr_message->k_queue_next != NULL)
	{
		curr_message = curr_message->k_queue_next;
		printf("Item %d = %d || Next = %p \n", i, curr_message->sender_pid, curr_message->k_queue_next);
		i++;
	}
	printf("\n");
}
