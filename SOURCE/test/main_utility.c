#include "k_queue.h"
#include "k_pcb.h"
#include "k_priority_queue.h"
#include "k_utility.h"
#include "k_init_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
	printf("TESTING UTILITY FUNCTION\n");
	int i, j;

	// Initialize structures;
	k_PCB_ptr pcb;
	extern k_queue_ptr k_allQ;
	k_allQ = k_queue_init();
	for (i=0; i<10;i++)
	{
		pcb = k_PCB_init(i,i,i,NULL);
		k_queue_enqueue(pcb, 1, k_allQ);
	}
	// At this point allQ has 9 processes with pid 0->9.
	k_PCB_ptr head = k_allQ->head;
	k_PCB_ptr tail = k_allQ->tail;

	printf("Test pid_to_PCB_ptr\n");

	printf("Test first process");
	pcb = k_pid_to_PCB_ptr(0);
	assert(pcb != NULL);
	assert(k_allQ->head == head);
	assert(k_allQ->tail == tail);
	assert(pcb->p_pid == 0);
	printf("---->PASS\n");	
	
	printf("Test last process");
	pcb = k_pid_to_PCB_ptr(9);
	assert(pcb != NULL);
	assert(k_allQ->head == head);
	assert(k_allQ->tail == tail);
	assert(pcb->p_pid == 9);
	printf("---->PASS\n");	
	
	printf("Test middle process");
	pcb = k_pid_to_PCB_ptr(4);
	assert(pcb != NULL);
	assert(k_allQ->head == head);
	assert(k_allQ->tail == tail);
	assert(pcb->p_pid == 4);
	printf("---->PASS\n");	

	printf("Test non-existant process");
	pcb = k_pid_to_PCB_ptr(24);
	assert(pcb == NULL);
	assert(k_allQ->head == head);
	assert(k_allQ->tail == tail);
	printf("---->PASS\n");	
	printf("UTILITY FUNCTIONS PASSED!\n\n");
}
