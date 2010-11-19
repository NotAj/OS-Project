#include "k_queue.h"

/****************************************************************
 Queue Data structure
 ----------------------------------------------------------------
 This structure is used for the allQ which contains all processes 
 in the RTX.
 It is also used inside the Priority Queue structure, which is an
 array of these queues. The readyQ and blockedQ are examples of 
 these. 

*****************************************************************/

/****************************************************************************
* Function      : k_queue_is_empty 
******************************************************************************
* Description   : This function determines if the queue specified is empty
* 				: If it is empty it returns 1, allowing it to be used in 
*				: conditional statements. This function is used by all other
*				: queue functions. 	
*           
* Assumptions   : Assumes a valid queue is specified. 
*****************************************************************************/
int k_queue_is_empty(k_queue_ptr Q) 
{
	if (Q == NULL)
		return NULL; // Do nothing if invalid pointer passed

	// If no items in queue, both head and tail will point to NULL
	// The result will be 1 if true, signifying an empty queue
	return (Q->head == NULL);
}

/****************************************************************************
* Function      : k_queue_enqueue 
******************************************************************************
* Description   : This function takes a pointer to a PCB and enqueues it to
* 				: the queue specified by a pointer to a queue. This function
*				: is used to enqueue to the allQ on initialization, and 
*				: enqueueing to the readyQ and blockedQ. To specify which 
*				: queue pointer to modify, the allQ parameter is used.				   
*              
* Assumptions   : Will do nothing in the case of enqueueing a NULL pointer.
*				: Assumes the PCB pointer given points to a valid PCB. 
*				: Assumes a valid queue is specified.
*****************************************************************************/
void k_queue_enqueue(k_PCB_ptr process, int all_Q, k_queue_ptr Q)
{
	if (Q == NULL)
		return NULL; // Do nothing if invalid pointer passed

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

/****************************************************************************
* Function      : k_queue_dequeue 
******************************************************************************
* Description   : This function dequeues the first pcb in the queue and returns 
* 				: a pointer to it. This function is only used to dequeue from 
*				: the readyQ and blockedQ. Because of this, the allQ parameter
*				: is not necessary.
*              
* Assumptions   : Will return NULL if dequeueing from an empty queue.
*				: Assumes a valid queue is specified.
*****************************************************************************/
k_PCB_ptr k_queue_dequeue(k_queue_ptr Q) 
{
	if (Q == NULL)
		return NULL; // Do nothing if invalid pointer passed

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

/****************************************************************************
* Function      : k_queue_remove
******************************************************************************
* Description   : This function removes a PCB from a queue with the PID 
*				: specified. This function is used on the readyQ when changing 
*				: the priority of a process. Because of this the allQ parameter
*				: is not necessary.
*              
* Assumptions   : Will return NULL if trying to remove from an empty queue or
*				: if no PCB on the queue has the PID specified.  
*				: Assumes a valid queue is specified.
*****************************************************************************/
k_PCB_ptr k_queue_remove(int pid, k_queue_ptr Q)
{
	if (Q == NULL)
		return NULL; // Do nothing if invalid pointer passed

	// Initialize local variables
	k_PCB_ptr prev_pcb;
	k_PCB_ptr current_pcb;

	current_pcb = Q->head;
	prev_pcb = NULL;

	// Will check if queue is empty, if it is, return NULL 
	if (k_queue_is_empty(Q)) 
		return NULL;

	// Iterate through queue, and stop when current_pcb holds PCB to be removed
	while(current_pcb->p_pid != pid) 
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
