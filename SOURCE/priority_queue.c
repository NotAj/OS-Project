#include "priority_queue.h"

int k_priority_queue_is_empty(k_priority_queue_ptr PQ) 
{
	// The priority queue must have an array of 4 queues, so check if these queues are empty or not
	int i;
	for (i=0; i<4; i++) // For the 4 priority levels
	{
		if (PQ->array[i]->head != NULL)
			return 0; // Will return as soon as one process found
	}
	// If here, no processes in the priority queue
	return 1;
}

void k_priority_queue_enqueue(k_PCB_ptr process, k_priority_queue_ptr PQ)
{
	if (process == NULL)
		return; // Trying to enqueue a NULL pointer, do nothing.
	
	if (process->p_priority < 0 || process->p_priority > 3)
		// Trying to enqueue a process with an invalid priority
		// Change the priority field to the lowest priority, and enqueue.
		process->p_priority = 3; 

	// Enqueue process onto queue indexed by p_priority
	// Only the readyQ uses this function so always specify 0 for allQ parameter
	k_queue_enqueue(process, 0, PQ->array[process->p_priority]);	
}

k_PCB_ptr k_priority_queue_dequeue(k_priority_queue_ptr PQ) 
{
	int i = 0;
	
	// Will iterate through PQ starting from highest priority until a non-empty queue is found. Remember to stop before trying to access invalid array index in case of empty PQ. 
	while (i<3 && k_queue_is_empty(PQ->array[i]))
		i++;
	
	// If i > 3, then entire queue is empty, so return NULL.
	if(i>3)
		return NULL;
	
	// Here i is index of highest priority non-empty queue, so dequeue from there.	
	return (k_queue_dequeue(PQ->array[i])); 
}

