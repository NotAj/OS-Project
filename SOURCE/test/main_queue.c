#include "k_queue.h"
#include "k_pcb.h"
#include "test_queue.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("Starting \n");
	int i, j;
 
	// Initializing queue
	
	i = -1 % 4;
	printf("%d", i);

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
	
	printf("TEST COMPLETE \n");

}
