#include "queue.h"
#include "priority_queue.h"
#include "test_queue.h"
#include "test_priority_queue.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("Starting \n");
	int i;

	// Initializing queue

	k_queue_ptr Q = malloc(sizeof(k_queue));

	test_queue_print(Q);
	printf("queue_is_empty = %d \n", k_queue_is_empty(Q));
	printf("Start Enqueue \n");
	test_queue_print(Q);
	for (i=0; i< 10; i++)
	{
		k_PCB_ptr pcb = malloc(sizeof(k_PCB));
		pcb->p_pid = i+1;
		k_queue_enqueue(pcb, 0, Q);
		test_queue_print(Q);
		printf("\n\n");
	}
	printf("Done Enqueue\n\n");
	printf("Start Dequeue\n");

	for (i=0; i< 10; i++)
	{
		k_PCB_ptr pcb;
		pcb = k_queue_dequeue(Q);
		printf("Dequeued PCB = %d || Next = %p\n", pcb->p_pid,pcb->k_queue_next);
		test_queue_print(Q);
		printf("\n\n");
	}
	printf("Done Dequeue\n\n");

	printf("Test dequeue Empty Queue\n");
	
	k_PCB_ptr pcb;
	pcb = k_queue_dequeue(Q);	
	if(pcb == NULL);
		printf("PASSED \n");
	pcb = k_queue_dequeue(Q);
	test_queue_print(Q);
	printf("\n\n");
	
	printf("Test remove empty queue \n");
	pcb = k_queue_remove(5, Q);	
	if(pcb == NULL);
		printf("PASSED \n");
	pcb = k_queue_remove(400, Q);
	test_queue_print(Q);
	printf("\n\n");

	printf("Testing Queue remove\n");
	printf("\n");
	for (i=0; i< 10; i++)
	{
		k_PCB_ptr pcb = malloc(sizeof(k_PCB));
		pcb->p_pid = i+1;
		k_queue_enqueue(pcb, 0, Q);
	}
	test_queue_print(Q);
	printf("\n\n");
	
	printf("REMOVING PID 1\n");
	pcb = k_queue_remove(1, Q);
	printf("Removed PCB = %d || Next = %p\n", pcb->p_pid, pcb->k_queue_next);	
	test_queue_print(Q);
	printf("\n");
	
	printf("REMOVING PID 10\n");
	pcb = k_queue_remove(10, Q);
	printf("Removed PCB = %d || Next = %p\n", pcb->p_pid, pcb->k_queue_next);
	test_queue_print(Q);
	printf("\n");
	
	printf("REMOVING PID 5\n");
	pcb = k_queue_remove(5, Q);
	printf("Removed PCB = %d || Next = %p\n", pcb->p_pid, pcb->k_queue_next);
	test_queue_print(Q);
	printf("\n");
	printf("Done testing remove\n\n");
	
	printf("Test remove nonexistent pid from queue\n");
	pcb = k_queue_remove(100, Q);
	if(pcb == NULL)
		printf("PASSED\n");
	test_queue_print(Q);


	
	printf("\n\n");
	printf("TESTING PRIORITY QUEUE\n");
	// Initialize priority queue
	k_priority_queue_ptr PQ = malloc(sizeof(k_priority_queue));
	for (i=0; i<4; i++)
	{
		PQ->array[i] = malloc(sizeof(k_queue));		
	}
	printf("Test print empty queue\n");
	test_priority_queue_print(PQ);
	
	int j;
	for (i=0; i<4; i++)
	{	
		for (j=0; j<4; j++)
		{
			k_PCB_ptr pcb = malloc(sizeof(k_PCB));
			pcb->p_pid = j*10 + i;
			pcb->p_priority = j;
			k_priority_queue_enqueue(pcb, PQ);
		}		
		test_priority_queue_print(PQ);
		printf("\n");
	}
	printf("Testing priority Queue dequeue\n");
	while(!k_priority_queue_is_empty(PQ))
	{
		pcb = k_priority_queue_dequeue(PQ);
		printf("Removed PCB = (%d,%d) || next = %p\n", pcb->p_pid, pcb->p_priority, pcb->k_queue_next);
		test_priority_queue_print(PQ);
		printf("\n\n");
	}

	printf("Testing enqueue NULL pcb\n");	
	k_priority_queue_enqueue(NULL, PQ);	
	test_priority_queue_print(PQ);
	printf("\n");	
	
	printf("Testing dequeue from empty priority queue\n");
	pcb = k_priority_queue_dequeue(PQ);
	printf("%p\n",pcb);
	if (pcb == NULL)
		printf("PASSED\n");	
	test_priority_queue_print(PQ);
	printf("\n");
	
	printf("Test adding PCB with invalid priority to PQ\n");
	pcb = malloc(sizeof(k_PCB));
	pcb->p_pid = 999;
	pcb->p_priority = 4;	
	k_priority_queue_enqueue(pcb, PQ);
	test_priority_queue_print(PQ);		

	pcb = malloc(sizeof(k_PCB));
	pcb->p_pid = 999;
	pcb->p_priority = -2;	
	k_priority_queue_enqueue(pcb, PQ);
	test_priority_queue_print(PQ);		

	pcb = malloc(sizeof(k_PCB));
	pcb->p_pid = 999;
	pcb->p_priority = 0;	
	k_priority_queue_enqueue(pcb, PQ);
	test_priority_queue_print(PQ);	

	pcb = malloc(sizeof(k_PCB));
	pcb->p_pid = 999;
	pcb->p_priority = 2;	
	k_priority_queue_enqueue(pcb, PQ);
	test_priority_queue_print(PQ);
	
	printf("Testing general enqueue & dequeuei\n");
	pcb = k_priority_queue_dequeue(PQ);
	printf("Removed PCB = (%d,%d) || next = %p\n", pcb->p_pid, pcb->p_priority, pcb->k_queue_next);
	test_priority_queue_print(PQ);

	pcb = k_priority_queue_dequeue(PQ);
	printf("Removed PCB = (%d,%d) || next = %p\n", pcb->p_pid, pcb->p_priority, pcb->k_queue_next);
	test_priority_queue_print(PQ);
		
}

