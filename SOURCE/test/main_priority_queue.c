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
	printf("\nTESTING PRIORITY QUEUE\n");
	int i=0;
	k_PCB_ptr pcb;
	k_PCB_ptr pcb2;
	k_PCB_ptr pcb3;
	k_priority_queue_ptr PQ;
	k_priority_queue_ptr PQ2;

	printf("Testing priority queue initialize");
	PQ = k_priority_queue_init();
	assert(PQ != NULL);
	printf("---->PASS\n");

	printf("Testing priority queue is empty");
	assert(k_priority_queue_is_empty(PQ));
//	for (i=0; i<4; i++)
//		assert (PQ->array[i]->head == NULL);
	printf("---->PASS\n");
		
	printf("Testing priority queue enqueue");	
	k_priority_queue_enqueue(NULL, PQ);	
	assert(k_priority_queue_is_empty(PQ));

	pcb = k_PCB_init(999,2,4,(void *)0x111);
	k_priority_queue_enqueue(pcb, PQ);
	assert(pcb->p_priority == 3);

	pcb->p_priority = -2;	
	k_priority_queue_enqueue(pcb, PQ);
	assert(pcb->p_priority == 3);

	pcb->p_priority = 0;	
	k_priority_queue_enqueue(pcb, PQ);
	assert(pcb->p_priority == 0);

	pcb->p_priority = 2;	
	k_priority_queue_enqueue(pcb, PQ);
	assert(pcb->p_priority == 2);
	
	printf("---->PASS\n");

	printf("Testing priority queue dequeue - empty");
	PQ2 = k_priority_queue_init();
	pcb2 = k_priority_queue_dequeue(PQ2);
	if (k_priority_queue_is_empty(PQ2))
		assert(pcb2 == NULL);
	printf("---->PASS\n");

	printf("Testing priority queue dequeue - nonempty");
	pcb2 = k_PCB_init(111,2,2,(void *)0x111);
	pcb3 = k_PCB_init(222,2,3,(void *)0x111);
	k_priority_queue_enqueue(pcb2, PQ2);
	k_priority_queue_enqueue(pcb3, PQ2);
//	test_priority_queue_print(PQ2);	
	pcb2 = k_priority_queue_dequeue(PQ2);
//	test_priority_queue_print(PQ2);	
	for(i=0;i<=pcb2->p_priority;i++)
		assert(k_queue_is_empty(PQ2->array[i]));
	printf("---->PASS\n");

/*	Previous code to do some stuff Ali wanted it to
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
*/
	printf("PRIORITY QUEUE PASSED =]\n\n");
}	
