#include "k_timeout_queue.h"

/****************************************************************
 Timeout Queue Data structure
 ----------------------------------------------------------------
 This structure is used to store timeout requests as they are waiting
 to time out. The queue is sorted based on time remaining till timeout.
 Each element in the queue has the timeout difference between it and the 
 element before it. 
*****************************************************************/

/****************************************************************************
* Function      : k_timeout_queue_enqueue 
******************************************************************************
* Description   : This function enqueues a msg_env (timeout request) into the queue
*		: based on how long until timeout. The first element contains the
* 		: the time until it times out...each subsequent request holds the  
*		: timeout time relative to the request before it
*           
* Assumptions   : 
*****************************************************************************/
void k_timeout_queue_enqueue(k_message_ptr msg, k_timeout_queue_ptr TQ)
{
	if (msg == NULL)
		return; // Trying to enqueue a NULL pointer, do nothing
	
	if (TQ->head == NULL)
	{
		TQ->head = msg; // if queue is empty, insert as first element
		msg->k_queue_next = NULL;
		return;
	}

	//create a temp variable to keep track of position in queue
	k_message_ptr curr_msg;
	k_message_ptr prev_msg;
	curr_msg = TQ->head;
	prev_msg = NULL;
	
	//insert as first element
	if (curr_msg->expiry_time > msg->expiry_time)
	{
		msg->k_queue_next = TQ->head;
		TQ->head->expiry_time -= msg->expiry_time;
		TQ->head = msg;
		return;	
	}

	//if queue is not empty...find the point of insertion 
	while(curr_msg == NULL || curr_msg->expiry_time <= msg->expiry_time) 
	{
		if (curr_msg == NULL) //If at end of queue
		{
			prev_msg->k_queue_next = msg;
			msg->k_queue_next = NULL;
			return;
		}
		msg->expiry_time -= curr_msg->expiry_time;
		prev_msg = curr_msg;
		curr_msg = curr_msg->k_queue_next;
	}
	///when at point of insertion (anywhere in the queue)
	prev_msg->k_queue_next = msg;
	msg->k_queue_next = curr_msg;

	//update next element of queue with correct timout time
	curr_msg->expiry_time -= msg->expiry_time;
	
	return;
}


/****************************************************************************
* Function      : k_timeout_queue_dequeue 
******************************************************************************
* Description   : This function dequeues a completed timeout request from the timeout
*		: queue and returns the pointer to the calling function. Only finished
* 		: requests can be dequeued
*           
* Assumptions   : 
*****************************************************************************/

k_message_ptr k_timeout_queue_dequeue (k_timeout_queue_ptr TQ)
{
	if (TQ == NULL)
		return NULL;
	if (TQ->head == NULL)
		return NULL;	
	if (TQ->head->expiry_time <= 0) //if element has expired
	{
		k_message_ptr TO_msg;
		TO_msg = TQ->head;
		TQ->head = TQ->head->k_queue_next;
		return TO_msg;
	}
	//if there is nothing to return
	return NULL;
}	
