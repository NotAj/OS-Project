#include "queue.h"

int k_queue_is_empty(k_queue_ptr Q) 
{
	// If no items in queue, both head and tail will point to NULL
	// The result will be 1 if true, signifying an empty queue
	if (Q->head == NULL)
		return 1;
	else
		return 0;
}
void k_queue_enqueue(k_PCB_ptr process, int all_Q, k_queue_ptr Q)
{
	if (process == NULL)
		return; // Trying to enqueue a NULL pointer, do nothing
	
	if (k_queue_is_empty(Q))
	{
		// Check if empty, if so set head and tail to point to process
		Q->head = process;
		Q->tail = process;
	}	
	else 
	{
		// Not empty, add process to end of queue. 
		// Update the next pointer of old tail and tail pointer.
		// Update the kernel pointer according to which queue was specified
		if (all_Q == 0) 
			Q->tail->k_queue_next = process;
		else	
			Q->tail->k_all_queue_next = process;
		// Process is not on a queue 
		// Next field in the k_PCB for this queue is already NULL, so do nothing.
	}
	// Tail set to point to process in both cases
	Q->tail = process;
}

k_PCB_ptr k_queue_dequeue(k_queue_ptr Q) 
{
	// Return NULL if Q is empty
	if(k_queue_is_empty(Q))
		return NULL;	
	// PCB to be returned
	k_PCB_ptr return_pcb;
	return_pcb = Q->head;
 	
	// Set head to next PCB in queue
	Q->head = return_pcb->k_queue_next;	
		
	// Check is queue is now empty
	if (Q->head == NULL)
	{
		Q->tail = NULL; // It is, so set tail to NULL too
	}
	return_pcb->k_queue_next = NULL; // PCB no longer on a queue so set next field to NULL
	
	// Return pointer to dequeued PCB
	return return_pcb;
}

k_PCB_ptr k_queue_remove(int PID, k_queue_ptr Q)
{
	// Initialize local variables
	k_PCB_ptr prev_pcb;
	k_PCB_ptr current_pcb;

	current_pcb = Q->head;
	prev_pcb = NULL;

	// Will check if queue is empty, if it is, return NULL 
	if (k_queue_is_empty(Q)) 
		return NULL;

	// Iterate through queue, and stop when current_pcb holds PCB to be removed
	while(current_pcb->p_pid != PID) 
	{
		prev_pcb = current_pcb; 
		current_pcb = current_pcb->k_queue_next;
		if (current_pcb == NULL) // Means pcb is not in queue
			return NULL;
	}

	// Here current_pcb points to pcb to be removed
	if (current_pcb == Q->head) //means the first item is to be removed
		return k_queue_dequeue(Q);
	
	// Here current_pcb is in middle or end of queue
	prev_pcb->k_queue_next = current_pcb->k_queue_next;
	if (current_pcb == Q->tail) // Check if removing tail
		Q->tail = prev_pcb;	
	
	return current_pcb;
}
