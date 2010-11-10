#include "test_tracebuffer.h"
#include <stdlib.h>
#include <stdio.h>

void test_tracebuffer_print(k_tracebuffer_ptr TB)
{
	int i;
	
	printf("**TRACEBUFFER**\n");
	
	i = TB->head;
	printf("HEAD = %d || TAIL = %d\n", TB->head, TB->tail);
	do
	{
		printf("I = %d : SID = %d || PID = %d || TYPE = %d || timestamp = %d\n", i, TB->buffer[i]->sender_pid, TB->buffer[i]->receiver_pid, TB->buffer[i]->msg_type, TB->buffer[i]->timestamp);
		(i++ % 16);
	} while (i != TB->tail);
	printf("\n");
}
