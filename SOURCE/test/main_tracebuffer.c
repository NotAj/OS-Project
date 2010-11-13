#include "k_tracebuffer.h"
#include "test_tracebuffer.h"
#include "k_init_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
	printf("Starting \n");
	int i, count;

	printf("TESTING TRACEBUFFERS\n\n");

	printf("Test initialize tracebuffer");	
	// Initializing tracebuffer
	k_tracebuffer_ptr TB = k_tracebuffer_init();
	assert(TB != NULL);
	assert(TB->head == 0);
	assert(TB->buffer != NULL);
	
	i = TB->head;
	do
	{
		assert(TB->buffer[i]->sender_pid == 0);
		assert(TB->buffer[i]->receiver_pid == 0);
 		assert(TB->buffer[i]->msg_type == 0);
		assert(TB->buffer[i]->timestamp == 0);
		i = (i+1) % TRACEBUFFER_SIZE;
		count++;
	} while (count < TRACEBUFFER_SIZE);
	printf("---->PASS\n");

	printf("Test update tracebuffer");
	for(i=0; i<16; i++)
	{
		k_tracebuffer_update(i, i+10, i+20, TB);
	}
	
	i = TB->head;
	count = 0;
	do
	{
		assert(TB->buffer[i]->sender_pid == (15 - count));
		assert(TB->buffer[i]->receiver_pid == 15 - count + 10);
 		assert(TB->buffer[i]->msg_type == 15 - count + 20);
		assert(TB->buffer[i]->timestamp == 0);
		i = (i+1) % TRACEBUFFER_SIZE;
		count++;
	} while (count < TRACEBUFFER_SIZE);
	printf("---->PASS\n");
	
	printf("Test overwrite tracebuffer");
	for(i=16; i<31; i++)
	{
		k_tracebuffer_update(i, i+10, i+20, TB);
	}
	
	count = 0;
	i = TB->head;
	do
	{
		assert(TB->buffer[i]->sender_pid == (30 - count));
		assert(TB->buffer[i]->receiver_pid == 30 - count + 10);
 		assert(TB->buffer[i]->msg_type == 30 - count + 20);
		assert(TB->buffer[i]->timestamp == 0);
		i = (i+1) % TRACEBUFFER_SIZE;
		count++;
	} while (count < TRACEBUFFER_SIZE);
	printf("---->PASS\n");

	
	printf("TRACEBUFFER PASSED\n");
}
