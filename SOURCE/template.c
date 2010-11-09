/****************************************************************
 Template Data Structure 
 ----------------------------------------------------------------
 This structure is used for the allQ which contains all processes 
 in the RTX.
 It is also used inside the Priority Queue structure, which is an
 array of these queues. The readyQ and blockedQ are examples of 
 these. 

*****************************************************************/

#include "queue.h"

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
	// If no items in queue, both head and tail will point to NULL
	// The result will be 1 if true, signifying an empty queue
	if (Q->head == NULL)
		return 1;
	else
		return 0;
}

