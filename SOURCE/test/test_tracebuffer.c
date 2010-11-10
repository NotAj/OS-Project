#include "test_tracebuffer.h"
#include <stdlib.h>
#include <stdio.h>

void test_tracebuffer_print(k_tracebuffer_ptr TB)
{
	int i, count;

// TODO Decide on scheme, head and tail or just head
/*	
	if (TB->head == TB->tail)
	{
		printf("Empty Tracebuffer - H%d T%d\n",TB->head, TB->tail);
		return;	
	}

*/

	printf("**TRACEBUFFER**\n");
	
	i = TB->head;
	count = 0;
	printf("HEAD = %d || TAIL = %d\n", TB->head, TB->tail);
	do
	{
		printf("I = %d : SID = %d || PID = %d || TYPE = %d || timestamp = %d\n", i, TB->buffer[i].sender_pid, TB->buffer[i].receiver_pid, TB->buffer[i].msg_type, TB->buffer[i].timestamp);
		i = (i+1) % TRACEBUFFER_SIZE;
		count++;
	} while (count < TRACEBUFFER_SIZE);
	//} while (i != (TB->tail+1) % TRACEBUFFER_SIZE); // TODO Decide on scheme
	printf("\n");
}
