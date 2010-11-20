#include "k_queue.h"
#include "k_pcb.h"
#include "k_priority_queue.h"
#include "k_init_struct.h"
#include "test_queue.h"
#include "test_priority_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
	printf("Starting \n");
	int i, j;
	k_PCB_ptr pcb; 
	
	printf("\n\n");
	printf("TESTING PRIORITY QUEUE\n");
	// Initialize priority queue
	k_priority_queue_ptr PQ = k_priority_queue_init();
	printf("Test print empty queue\n");
	test_priority_queue_print(PQ);
	
	for (i=0; i<4; i++)
	{	
		for (j=0; j<4; j++)
		{
			pcb = malloc(sizeof(k_PCB));
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
	printf("\n\n");
}	
