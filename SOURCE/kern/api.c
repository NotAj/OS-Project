#include "api.h"

/****************************************************************
 User API
 ----------------------------------------------------------------
 This file has all the user visible API function available to 
 user processes. These primitives disable interrupts, then call the 
 kernel version of these primitives. They reenable interrupts before
 returning. All primitives return 0 on success.

*****************************************************************/

/*************************
* Scheduler primitives 
*************************/
int release_processor()
{
	int code;
	atomic(1);
	code = k_release_processor();
	atomic(0);
	return code;	
}

int request_process_status(MsgEnv *msg_env_ptr)
{
	int code;
	atomic(1);
	code = k_request_process_status(msg_env_ptr);	
	atomic(0);
	return code;
}

int terminate()
{
/*	MsgEnv *msg = request_msg_env(); //Assuming this doesn block TODO
	sprintf(msg->msg_text, "Process %d requested a terminate. Exiting\n", k_current_process->p_pid); 
	send_console_chars(msg);
	while(receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
*/
	atomic(1);
	k_terminate(ERROR_NONE);
	atomic(0);
	// Should never return since terminate kills the process. Return to stop compile warnings
	return 0; 
}

// Terminate function for handling all non-user shutdowns
void die(int code)
{
/*	MsgEnv *msg = request_msg_env(); //Assuming this doesn block TODO

	k_current_process->k_atomic_count = 1;
	atomic(0);

	switch (code)
	{
		case SIGINT:
			sprintf(msg->msg_text, "User Requested Shutdown.\nExiting RTX. Current Process = %d\n", k_current_process->p_pid);
			break;
		case SIGQUIT:
			sprintf(msg->msg_text, "User Requested Shutdown.\nExiting RTX. Current Process = %d\n", k_current_process->p_pid);
			break;
		default:
			sprintf(msg->msg_text, "CRITICAL ERROR.\nExiting RTX. Current Process = %d\n", k_current_process->p_pid);
			break;
	}
	send_console_chars(msg);
	printf("CurrProc=%d, outBuf=%d\n", k_current_process->p_pid,k_output_buf->wait_flag);
*/	atomic(1);
	k_terminate();
	atomic(0);
}

int change_priority(int new_priority, int target_process_id)
{
	int code;
	atomic(1);
	code = k_change_priority(new_priority, target_process_id);
	atomic(0);
	return code;
}

/*************************
* IPC primitives 
*************************/
int send_message(int dest_process_id, MsgEnv *msg_envelope)
{
	int code;
	atomic(1);
	code = k_send_message(dest_process_id, msg_envelope);
	atomic(0);
	return code;
}

MsgEnv *receive_message()
{
	MsgEnv *msg;
	atomic(1);
	msg = k_receive_message();
	atomic(0);
	return msg;
}

int release_msg_env(MsgEnv *msg_env_ptr)
{
	int code;
	atomic(1);
	code = k_release_msg_env(msg_env_ptr);
	atomic(0);
	return code;
}

MsgEnv *request_msg_env()
{
	MsgEnv *msg;
	atomic(1);
	msg = k_request_msg_env();
	atomic(0);
	return msg;
}

int get_trace_buffers(MsgEnv *message_envelope)
{
	int code;
	atomic(1);
	code = k_get_trace_buffers(message_envelope);	
	atomic(0);
	return code;
}

MsgEnv_queue_ptr MsgEnv_queue_init()
{
	MsgEnv_queue_ptr messageQ;
	atomic(1);
	messageQ = k_message_queue_init();
	atomic(0);
	return messageQ;
}

int MsgEnv_queue_is_empty(MsgEnv_queue_ptr MQ)
{
	int code;
	atomic(1);
	code = k_message_queue_is_empty(MQ);
	atomic(0);
	return code;
}

void MsgEnv_queue_enqueue(MsgEnv *message, MsgEnv_queue_ptr MQ) 
{
	atomic(1);
	k_message_queue_enqueue(message, MQ);
	atomic(0);
	return;
}

MsgEnv *MsgEnv_queue_dequeue(MsgEnv_queue_ptr MQ)
{
	MsgEnv *msg;
	atomic(1);
	msg = k_message_queue_dequeue(MQ);
	atomic(0);
	return msg;
}
/*************************
* Timing primitives 
*************************/
int request_delay(int time_delay, int wakeup_code, MsgEnv *message_envelope)
{
	int code;
	atomic(1);
	code = k_request_delay(time_delay, wakeup_code, message_envelope);
	atomic(0);
	return code;
}

/*************************
* IO primitives 
*************************/
int send_console_chars(MsgEnv *message_envelope)
{
	int code;
	atomic(1);
	code = k_send_console_chars(message_envelope);
	atomic(0);
	return code;
}

int get_console_chars(MsgEnv *message_envelope)
{
	int code;
	atomic(1);
	code = k_get_console_chars(message_envelope);
	atomic(0);
	return code;
}
