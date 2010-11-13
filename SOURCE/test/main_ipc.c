#include "k_message.h"
#include "k_message_queue.h"
#include "test_message_queue.h"
#include "k_init_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//ipc
int main()
{
	printf("TESTING MESSAGE QUEUE \n");
	int i, j;
	k_message_ptr message; 
	k_message_queue_ptr MQ;

	printf("Test message initialize");
	message = k_message_init();
	assert(message != NULL);
	printf("---->PASS\n");
	
	printf("Test message queue initialize");
	MQ = k_message_queue_init();
	// Test if MQ initialized to NULL head and tailo
	assert(MQ->head == NULL && MQ->tail == NULL);
	printf("---->PASS\n");

	printf("Test message queue is empty");
	assert(k_message_queue_is_empty(MQ));
	printf("---->PASS\n");
	
	printf("Test message queue enqueue ");
	k_message_ptr add[6];
	for (i=0; i< 5; i++)
	{
		message = k_message_init();
		message->sender_pid = i;
		message->receiver_pid = i+1;
		message->msg_type = i+2;
		message->msg_size = i+3;
		message->expiry_time = i+4;
		k_message_queue_enqueue(message, MQ);
		add[i] = message; 
	}
	add[5] = NULL;
	assert(MQ->head == add[0]);
	assert(MQ->tail == add[4]);
	message = MQ->head;
	for (i=0; i<5; i++)
	{
		assert(message->sender_pid == i);
		assert(message->receiver_pid == i+1);
		assert(message->msg_type == i+2);
		assert(message->msg_size == i+3);
		assert(message->expiry_time == i+4);
		assert(message->k_queue_next == add[i+1]);		
		message = message->k_queue_next;
	}
	printf("---->PASS\n");
	
	printf("Test queue dequeue");
	message = k_message_queue_dequeue(MQ);
	assert(message->sender_pid == 0);
	assert(message->receiver_pid == 1);
	assert(message->msg_type == 2);
	assert(message->msg_size == 3);
	assert(message->expiry_time == 4);
	assert(message->k_queue_next == NULL);
	// After dequeue, first item is removed.
	assert(MQ->head == add[1]);
	assert(MQ->tail == add[4]);
	message = MQ->head;
	for (i=1; i<5; i++)
	{
		assert(message->sender_pid == i);
		assert(message->receiver_pid == i+1);
		assert(message->msg_type == i+2);
		assert(message->msg_size == i+3);
		assert(message->expiry_time == i+4);
		assert(message->k_queue_next == add[i+1]);		
		message = message->k_queue_next;
	}
	printf("---->PASS\n");

	printf("Test dequeue empty Message Queue");
	for (i=1; i<5; i++)
	{
		message = k_message_queue_dequeue(MQ);
	}
	message = k_message_queue_dequeue(MQ);
	assert(message == NULL);
	assert(k_message_queue_is_empty(MQ));
	printf("---->PASS\n");
	
	printf("MESSAGE QUEUE PASSED\n");

}
