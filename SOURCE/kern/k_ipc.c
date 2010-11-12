int k_send_message (int dest_process_id, MsgEnv * msg_env_ptr)
 {
	PCB_ptr dest_PCB;
	//Function takes a PID, and returns a pointer to its PCB
	dest_PCB = PID_to_PCB_ptr(dest_process_id); 
	msg_env_ptr->sender_pid = k_current_process->p_pid;
	msg_env_ptr->receiver_pid = dest_process_id;
	MEQ_enqueue(msg_env_ptr, dest_PCB->p_received_MsgEnvQ);
	If (dest_PCB->p_status == STATUS_BLOCKED_ON_RECEIVE) 
	{
		dest_PCB->p_status = STATUS_READY;
		k_message_queue_enqueue(dest_PCB, k_readyQ);
	}
	update_TB(k_current_process->p_pid, dest_process_id, msg_env_ptr->msg_type, k_clock_tick, k_send_TB); 
	return 1;
 }  

MsgEnv* k_recieve_message () 
 {
	MsgEnv *return_msg;
	if(is_empty(k_current_process->p_received_MsgEnvQ)) //self explanitory
	{
		if(k_current_process->p_status == STATUS_IPROCESS) //PCB is an iprocess 
			return NULL;
		k_current_process->p_status = STATUS_BLOCKED_ON_RECEIVE;

		//This will perform a process switch to the next ready process
		process_switch();
		//Process will resume here once when picked to execute
	}
	//Function is here when a message is in the received message queue for the current process
	return_msg = k_message_queue_dequeue(k_current_process->p_received_MsgEnvQ);
	update_TB(return_msg->sender_pid, current_process->p_pid, return_msg->msg_type, k_clock_tick, k_recieve_TB);
 	return return_msg;
 }

MsgEnv* k_request_msg_env () 
 {
	while(is_empty(k_freeQ){
		if(k_current_process->p_status == STATUS_IPROCESS)
			return NULL;
		k_blocked_queue_enqueue(k_current_process, k_blockedQ);
		k_current_process->p_status = STATUS_BLOCKED_ON_RESOURCE;
		
		//This will perform a process switch to next ready process
		process_switch();	
		//Process will resume here when chosen to execute again
	}
	//Function is here when there is an envelope available
	return (k_message_queue_dequeue(k_freeQ);
 }

int k_release_msg_env (MsgEnv * msg_env_ptr) 
{
	msg_env_prt->sender_pid = 0;
	msg_env_prt->receiver_pid = 0;
	msg_env_prt->msg_type = 0;
	msg_env_prt->msg_size = 0;
	msg_env_prt->expiry_time = 0;
	
	PCB_Ptr ready_process;	

	k_message_queue_enqueue(msg_env_ptr, k_freeQ);
	ready_process = k_blocked_queue_dequeue(k_blockedQ); 
	ready_process->p_status = STATUS_READY;
	k_ready_queue_enqueue(ready_process, k_readyQ);
	
	return 1;
}
