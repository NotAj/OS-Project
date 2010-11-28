#include "k_ipc.h"

/****************************************************************
 IPC Data Structure 
 ----------------------------------------------------------------

 These functions provide functionality to the IPC. It allows for 
 processes to send, receive, request and release message envelopes.

*****************************************************************/

/****************************************************************************
* Function      : k_send_message 
******************************************************************************
* Description   : This function sends a message envelope to the indicated destination process.
* 				: If the destination process id does not exist it returns 0.
*				: If the destination process is blocked on receive, it will
*				: be set to ready. The send trace buffer is updated.
*           
* Assumptions   : Assumes the message has been composed and all fields excluding the sender
*		: pid and receiver pid have been initialized. Assumes the envelope is not NULL.
*****************************************************************************/

int k_send_message (int dest_process_id, MsgEnv * msg_env_ptr)
 {
	k_PCB_ptr dest_PCB;
	//Function takes a PID, and returns a pointer to its PCB
	dest_PCB = k_pid_to_PCB_ptr(dest_process_id);
	if(dest_PCB == NULL || msg_env_ptr == NULL)
		return ERROR_INVALID_PARAMETERS; 
	msg_env_ptr->sender_pid = k_current_process->p_pid;
	msg_env_ptr->receiver_pid = dest_process_id;
		
	k_message_queue_enqueue(msg_env_ptr, dest_PCB->k_received_message_queue);
	if (dest_PCB->p_status == STATUS_BLOCKED_ON_RECEIVE) 
	{
		dest_PCB->p_status = STATUS_READY;
		k_priority_queue_enqueue(dest_PCB, k_readyPQ);
	}
	k_tracebuffer_update(k_current_process->p_pid, dest_process_id, msg_env_ptr->msg_type, k_sendTB); 
	return ERROR_NONE;
 }  

/****************************************************************************
* Function      : k_receive_message 
******************************************************************************
* Description   : This function returns a message envelope from its received envelope queue.
* 				: If the received envelope queue is empty the process will
*				: become blocked on receive or NULL will be returned if it
*				: is an iprocess. The receive trace buffer is updated.
*****************************************************************************/

MsgEnv* k_receive_message () 
 {
	k_message_ptr return_msg;
	if(k_message_queue_is_empty(k_current_process->k_received_message_queue)) //self explanatory
	{
		if(k_current_process->p_status == STATUS_IPROCESS) //PCB is an iprocess 
			return NULL;
		k_current_process->p_status = STATUS_BLOCKED_ON_RECEIVE;

		//This will perform a process switch to the next ready process
		k_process_switch();
		//Process will resume here once when picked to execute
	}
	//Function is here when a message is in the received message queue for the current process
	return_msg = k_message_queue_dequeue(k_current_process->k_received_message_queue);
	k_tracebuffer_update(return_msg->sender_pid, k_current_process->p_pid, return_msg->msg_type, k_receiveTB);
 	return return_msg;
 }

/****************************************************************************
* Function      : k_request_msg_env 
******************************************************************************
* Description   : This function returns an empty message envelope.
* 				: As long as the free envelope queue is empty the process will
*				: become blocked on resource or NULL will be returned if it
*				: is an iprocess.
*****************************************************************************/

MsgEnv* k_request_msg_env () 
 {
	while(k_message_queue_is_empty(k_freeMQ)){
		if(k_current_process->p_status == STATUS_IPROCESS)
			return NULL;
		k_priority_queue_enqueue(k_current_process, k_blockedPQ);
		k_current_process->p_status = STATUS_BLOCKED_ON_RESOURCE;

		//This will perform a process switch to next ready process
		k_process_switch();	
		//Process will resume here when chosen to execute again
	}
	//Function is here when there is an envelope available
	return (k_message_queue_dequeue(k_freeMQ));
 }

/****************************************************************************
* Function      : k_release_msg_env
******************************************************************************
* Description   : This function clears all numerical fields of an envelope and retuns it to
*		: the free envelope queue.
* 				: If there is a PCB in the blocked queue, it will be removed
*				: from the blocked queue, set to ready and placed in the 
*				: ready queue.
*           
* Assumptions   : Assumes envelope being passed is not NULL.
*****************************************************************************/

int k_release_msg_env (MsgEnv * msg_env_ptr) 
 {
	if(msg_env_ptr == NULL)
		return ERROR_INVALID_PARAMETERS;
	msg_env_ptr->sender_pid = 0;
	msg_env_ptr->receiver_pid = 0;
	msg_env_ptr->msg_type = 0;
	msg_env_ptr->msg_size = 0;
	msg_env_ptr->expiry_time = 0;
	
	k_PCB_ptr ready_process;	
	
	k_message_queue_enqueue(msg_env_ptr, k_freeMQ);
	if(!(k_priority_queue_is_empty(k_blockedPQ))) 
	 {	
		ready_process = k_priority_queue_dequeue(k_blockedPQ); 
		ready_process->p_status = STATUS_READY;
		k_priority_queue_enqueue(ready_process, k_readyPQ); 
	 }
	return ERROR_NONE;
 }

/****************************************************************************
* Function      :  k_get_trace_buffers
******************************************************************************
* Description   : This function accepts a msg env pointer and goes through the queue
*				: of all PCB's adding the PID, priority, and status of each to the 
*				: text of the message. 
* 
* Assumptions   :  
*****************************************************************************/
int k_get_trace_buffers(MsgEnv * message_envelope)
{
	if (message_envelope == NULL)
	{
		return ERROR_INVALID_PARAMETERS;	
	}

	k_trace_ptr tb;
	int i, offset, spid, rpid, msgtyp, time;
	i = k_sendTB->head;
	offset = 0;
	offset += sprintf(message_envelope->msg_text + offset, "%30s\n%10s %10s %10s %10s\n","SENT MESSAGES", "Sndr PID",  "Rcvr PID",  "Msg Type",  "Timestamp");

	do 
	{			
		tb = k_sendTB->buffer[i];
		spid = tb->sender_pid;		
		rpid = tb->receiver_pid;
		msgtyp = tb->msg_type;
		time = tb->timestamp;
		offset += sprintf(message_envelope->msg_text + offset, "%10d %10d %10d %10d\n", spid, rpid, msgtyp, time); 
		i = (i+1)%16;
	} while(i != k_sendTB->head);
	
	offset += sprintf(message_envelope->msg_text + offset, "\n");
	offset += sprintf(message_envelope->msg_text + offset, "%30s\n%10s %10s %10s %10s\n","RECEIVED MESSAGES", "Sndr PID",  "Rcvr PID",  "Msg Type",  "Timestamp");
	do
	{		
		tb = k_receiveTB->buffer[i]; 	
		spid = tb->sender_pid;		
		rpid = tb->receiver_pid;
		msgtyp = tb->msg_type;
		time = tb->timestamp;
		offset += sprintf(message_envelope->msg_text + offset, "%10d %10d %10d %10d\n", spid, rpid, msgtyp, time); 

		i = (i+1)%16;
	} while(i != k_receiveTB->head);
		
	return ERROR_NONE; 	//once the message envelope is populated with the
					//information for all processes
}
