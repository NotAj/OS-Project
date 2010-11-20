#include "k_queue.h"
#include "k_pcb.h"
#include "test_queue.h"
#include "k_init_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
	printf("TESTING QUEUE \n");
	int i, j;
	k_PCB_ptr pcb; 
	k_queue_ptr Q;

	printf("Test pcb initialize");
	pcb = k_PCB_init(1,2,3,(void *)0x111);
	// Test if fields initialized properly
	assert(pcb->p_pid == 1);
	assert(pcb->p_status == 2);
	assert(pcb->p_priority == 3);
	assert(pcb->k_start_address == (void *)0x111);
	printf("---->PASS\n");
	
	printf("Test queue initialize");
	Q = k_queue_init();
	// Test if Q initialized to NULL head and tailo
	assert(Q->head == NULL && Q->tail == NULL);
	printf("---->PASS\n");

	printf("Test queue is empty");
	assert(k_queue_is_empty(Q));
	printf("---->PASS\n");
	
	printf("Test queue enqueue ");
	k_PCB_ptr add[6];
	for (i=0; i< 5; i++)
	{
		pcb = k_PCB_init(i,i+1,i+2, NULL);
		k_queue_enqueue(pcb, 0, Q);
		add[i] = pcb; 
	}
	add[5] = NULL;
	assert(Q->head == add[0]);
	assert(Q->tail == add[4]);
	pcb = Q->head;
	for (i=0; i<5; i++)
	{
		assert(pcb->p_pid == i);
		assert(pcb->p_status == i+1);
		assert(pcb->p_priority == i+2);
		assert(pcb->k_queue_next == add[i+1]);		
		pcb = pcb->k_queue_next;
	}
	printf("---->PASS\n");
	
	printf("Test queue dequeue");
	pcb = k_queue_dequeue(Q);
	assert(pcb->p_pid == 0);
	assert(pcb->p_status == 1);
	assert(pcb->p_priority == 2);
	assert(pcb->k_queue_next == NULL);
	// After dequeue, first item is removed.
	assert(Q->head == add[1]);
	assert(Q->tail == add[4]);
	pcb = Q->head;
	for (i=1; i<5; i++)
	{
		assert(pcb->p_pid == i);
		assert(pcb->p_status == i+1);
		assert(pcb->p_priority == i+2);
		assert(pcb->k_queue_next == add[i+1]);		
		pcb = pcb->k_queue_next;
	}
	printf("---->PASS\n");
	
	printf("Test queue remove");	
	// Remove non-existant PID
	pcb = k_queue_remove(10, Q);	
	assert(pcb == NULL);	
	assert(Q->head == add[1]);
	assert(Q->tail == add[4]);
		
	pcb = Q->head;
	for (i=1; i<5; i++)
	{
		assert(pcb->p_pid == i);
		assert(pcb->p_status == i+1);
		assert(pcb->p_priority == i+2);
		assert(pcb->k_queue_next == add[i+1]);		
		pcb = pcb->k_queue_next;	
	}
	// Remove last item
	pcb = k_queue_remove(4,Q);
	add[4] = NULL;
	assert(pcb->p_pid == 4);
	assert(pcb->p_status == 5);
	assert(pcb->p_priority == 6);
	assert(pcb->k_queue_next == NULL);				
	assert(Q->head == add[1]);
	assert(Q->tail == add[3]);

	pcb = Q->head;
	for (i=1; i<4; i++)
	{
		assert(pcb->p_pid == i);
		assert(pcb->p_status == i+1);
		assert(pcb->p_priority == i+2);
		assert(pcb->k_queue_next == add[i+1]);		
		pcb = pcb->k_queue_next;	
	}
	// Remove item in middle
	pcb = k_queue_remove(2,Q);
	add[2] = add[3];
	assert(pcb->p_pid == 2);
	assert(pcb->p_status == 3);
	assert(pcb->p_priority == 4);
	assert(pcb->k_queue_next == NULL);				
	assert(Q->head == add[1]);
	assert(Q->tail == add[3]);
		
	pcb = Q->head;	
	for (i=1; (i<4); i++)
	{
		if (i != 2)
		{
			assert(pcb->p_pid == i);
			assert(pcb->p_status == i+1);
			assert(pcb->p_priority == i+2);
			assert(pcb->k_queue_next == add[i+1]);		
			pcb = pcb->k_queue_next;
		}
	}
	printf("---->PASS\n");


	printf("Test dequeue empty Queue");
	for (i=0; i<3; i++)
	{
		pcb = k_queue_dequeue(Q);
	}
	pcb = k_queue_dequeue(Q);
	assert(pcb == NULL);
	assert(k_queue_is_empty(Q));
	printf("---->PASS\n");
	
	printf("Test remove empty queue ");
	pcb = k_queue_remove(1,Q);
	assert(pcb == NULL);
	assert(k_queue_is_empty(Q));
	printf("---->PASS\n");

	printf("QUEUE PASSED\n");

}
