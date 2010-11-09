#include "test_priority_queue.h"
#include "test_queue.h"
#include <stdlib.h>
#include <stdio.h>

void test_priority_queue_print(k_priority_queue_ptr PQ)
{
	if (k_priority_queue_is_empty(PQ))
	{
		printf("Empty Queue \n\n");
		return;
	}	

	int i;	

	printf("**PRIORITY QUEUE**\n");
	for (i=0; i<4; i++)
	{ 
		printf("Priority %d ------------------- \n", i);
		test_queue_print(PQ->array[i]);
	}
	printf("\n");
}
