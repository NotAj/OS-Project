#include "test_queue.h"
#include <stdlib.h>
#include <stdio.h>

void test_queue_print(k_queue_ptr Q)
{
	int i = 0;
	k_PCB_ptr curr_PCB = NULL;
	if (k_queue_is_empty(Q))
	{	
		printf("Empty Queue \n\n");
		return;
	}
	printf("**QUEUE**\n");
	curr_PCB = Q->head;	
	printf("Item %d = %d || Next = %p \n", i, curr_PCB->p_pid, curr_PCB->k_queue_next);
	i++;	
	while (curr_PCB->k_queue_next != NULL)
	{
		curr_PCB = curr_PCB->k_queue_next;
		printf("Item %d = %d || Next = %p \n", i, curr_PCB->p_pid, curr_PCB->k_queue_next);
		i++;
	}
	printf("\n");
}
