#include "message_queue.h"
#include <stdlib.h>

/****************************************************************
 Message Queue Data Structure 
 ----------------------------------------------------------------
 This structure is used for the received messages queue inside each
 PCB as well as the free envelope queue.  
 The functions are almost identical to the queue structure,
 but they deal with message envelope pointers instead of message 
 pointers.

*****************************************************************/

/****************************************************************************
* Function      : k_message_queue_is_empty 
******************************************************************************
* Description   : This function determines if the queue specified is empty
* 				: If it is empty it returns 1, allowing it to be used in 
*				: conditional statements. This function is used by all other
*				: message queue functions. 	
*           
* Assumptions   : Assumes a valid queue is specified. 
*****************************************************************************/
int k_message_queue_is_empty(k_message_queue_ptr MQ) 
{
	// If no items in queue, both head and tail will point to NULL
	// The result will be 1 if true, signifying an empty queue
	return (MQ->head == NULL);
}

/****************************************************************************
* Function      : k_message_queue_enqueue 
******************************************************************************
* Description   : This function takes a pointer to a message and enqueues it to
* 				: the queue specified.
*				: It is used by send_message, to enqueue onto the receive queue
*				: of local messages and by release_msg_env.  
*              
* Assumptions   : Will do nothing in the case of enqueueing a NULL pointer.
*				: Assumes the message pointer given points to a valid message. 
*				: Assumes a valid queue is specified.
*****************************************************************************/
void k_message_queue_enqueue(MsgEnv_ptr message, k_message_queue_ptr MQ)
{
	if (message == NULL)
		return; // Trying to enqueue a NULL pointer, do nothing
	
	if (k_message_queue_is_empty(MQ))
	{
		// Check if empty, if so set head and tail to point to message
		MQ->head = message;
		MQ->tail = message;
	}	
	else 
	{
		// Not empty, add message to end of queue. 
		// Update the next pointer of old tail and tail pointer.
		// Update the kernel pointer according to which queue was specified
		MQ->tail->k_queue_next = message;
		// Process is not on a queue 
		// Next field in the k_message for this queue is already NULL, so do nothing.
	}
	// Tail set to point to message in both cases
	MQ->tail = message;
}

/****************************************************************************
* Function      : k_message_queue_dequeue 
******************************************************************************
* Description   : This function dequeues the first message in the queue and 
* 				: returns a  pointer to it. This function is used by functions
*				: which want to dequeue from message queues, (allocate_env, 
*				: receive_message) 
*              
* Assumptions   : Will return NULL if dequeueing from an empty queue.
*				: Assumes a valid queue is specified.
*****************************************************************************/
MsgEnv_ptr k_message_queue_dequeue(k_message_queue_ptr MQ) 
{
	// Return NULL if Q is empty
	if(k_message_queue_is_empty(MQ))
		return NULL;	
	// Message to be returned
	MsgEnv_ptr return_message;
	return_message = MQ->head;
 	
	// Set head to next message in queue
	MQ->head = return_message->k_queue_next;	
		
	// Check is queue is now empty
	if (MQ->head == NULL)
	{
		MQ->tail = NULL; // It is, so set tail to NULL too
	}
	return_message->k_queue_next = NULL; // Message no longer on a queue so set next field to NULL
	
	// Return pointer to dequeued message
	return return_message;
}

