#include "k_priority_queue.h"

/****************************************************************
 Priority Queue Data structure
 ----------------------------------------------------------------
 This structure is used for the scheduling queues readyQ and 
 blockedQ. The structure is an array of queues, with each element
 in the array holding a queue for the corresponding priority. 
 PCBs are added and removed from the queue based on this priority value. 

*****************************************************************/

/****************************************************************************
* Function      : k_priority_queue_is_empty 
******************************************************************************
* Description   : This function determines if the priority queue specified is 
*				: empty.
* 				: If it is empty it returns 1, allowing it to be used in 
*				: conditional statements.
*           
* Assumptions   : Assumes a valid priority queue is specified. 
*****************************************************************************/
int k_priority_queue_is_empty(k_priority_queue_ptr PQ) 
{
	if (PQ == NULL)
		return 1; // Return empty code if invalid pointer passed

	// The priority queue must have an array of 4 queues, so check if these queues are empty or not
	int i;
	for (i=0; i< PRIORITY_NUM; i++) // For the 4 priority levels
	{
		if (PQ->array[i]->head != NULL)
			return 0; // Will return as soon as one process found
	}
	// If here, no processes in the priority queue
	return 1;
}

/****************************************************************************
* Function      : k_priority_queue_enqueue 
******************************************************************************
* Description   : This function enqueues a PCB to the queue corresponding to 
*				: the process' priority. This function is used to enqueue to 
*				: the readyQ and blockedQ so there is no need to specify the
*				: allQ parameter. 
*           
* Assumptions   : Will do nothing if attempting to enqueue a NULL pointer
*				: If a PCB is enqueued with an invalid priority, it will be
*				: changed to the lowest priority and enqueued.
*				: Assumes the PCB pointer given points to a valid PCB.
*				: Assumes a valid priority queue is specified. 
*****************************************************************************/
void k_priority_queue_enqueue(k_PCB_ptr process, k_priority_queue_ptr PQ)
{
	if (PQ == NULL)
		return; // Do nothing if invalid pointer passed

	if (process == NULL)
		return; // Trying to enqueue a NULL pointer, do nothing.
	
	if (process->p_priority < 0 || process->p_priority >=  PRIORITY_NUM)
		// Trying to enqueue a process with an invalid priority
		// Change the priority field to the lowest priority, and enqueue.
		process->p_priority = 3; 

	// Enqueue process onto queue indexed by p_priority
	// Only the readyQ uses this function so always specify 0 for allQ parameter
	k_queue_enqueue(process, 0, PQ->array[process->p_priority]);	
}
/****************************************************************************
* Function      : k_priority_queue_dequeue 
******************************************************************************
* Description   : This function dequeues the first pcb in the priority queue 
*				: with the highest priority.This function is only used to 
*				: dequeue from the readyQ and blockedQ. Because of this, 
*				: the allQ parameter is not necessary.
*              
* Assumptions   : Will return NULL if dequeueing from an empty priority queue.
*				: Assumes a valid priority queue is specified.
****************************************************************************/
k_PCB_ptr k_priority_queue_dequeue(k_priority_queue_ptr PQ) 
{
	if (PQ == NULL)
		return NULL; // Do nothing if invalid pointer passed

	// If priority queue is empty, return NULL.
	if (k_priority_queue_is_empty(PQ))
		return NULL;

	int i = 0;
	
	// Will iterate through PQ starting from highest priority until a non-empty queue is found. 
	// i will always contain a valid index, because empty queue case has already been handled. 
	while (k_queue_is_empty(PQ->array[i]))
		i++;
	
	// Here i is index of highest priority non-empty queue, so dequeue from there.	
	return (k_queue_dequeue(PQ->array[i])); 
}

/****************************************************************************
* Function      : k_priority_queue_remove
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
k_PCB_ptr k_priority_queue_remove(int pid, k_priority_queue_ptr PQ)
{
	if (PQ == NULL)
		return NULL; // Do nothing if invalid pointer passed
	
	k_PCB_ptr removed_pcb;	
	removed_pcb = k_pid_to_PCB_ptr(pid);
	if (removed_pcb == NULL)
		return NULL; // If specified PID is invalid, do nothing
	
	// Check if PCB has valid priority, if invalid do nothing
	if (removed_pcb->p_priority < 0 || removed_pcb->p_priority >= PRIORITY_NUM)
		return NULL;	

	return k_queue_remove(pid, PQ->array[removed_pcb->p_priority]);
}

