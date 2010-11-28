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
	k_atomic(1);
	code = k_release_processor();
	k_atomic(0);
	return code;	
}

int request_process_status(MsgEnv *msg_env_ptr)
{
	int code;
	k_atomic(1);
	code = k_request_process_status(msg_env_ptr);	
	k_atomic(0);
	return code;
}

int terminate()
{
	k_atomic(1);
	k_terminate(ERROR_NONE);
	k_atomic(0);
	// Should never return since terminate kills the process. Return to stop compile warnings
	return 0; 
}

// Terminate function for handling all non-user shutdowns
void die(int code)
{
	k_atomic(1);
	k_terminate(ERROR_SIG);
	k_atomic(0);
}

int change_priority(int new_priority, int target_process_id)
{
	int code;
	k_atomic(1);
	code = k_change_priority(new_priority, target_process_id);
	k_atomic(0);
	return code;
}

/*************************
* IPC primitives 
*************************/
int send_message(int dest_process_id, MsgEnv *msg_envelope)
{
	int code;
	k_atomic(1);
	code = k_send_message(dest_process_id, msg_envelope);
	k_atomic(0);
	return code;
}

MsgEnv *receive_message()
{
	MsgEnv *msg;
	k_atomic(1);
	msg = k_receive_message();
	k_atomic(0);
	return msg;
}

int release_msg_env(MsgEnv *msg_env_ptr)
{
	int code;
	k_atomic(1);
	code = k_release_msg_env(msg_env_ptr);
	k_atomic(0);
	return code;
}

MsgEnv *request_msg_env()
{
	MsgEnv *msg;
	k_atomic(1);
	msg = k_request_msg_env();
	k_atomic(0);
	return msg;
}

int get_trace_buffers(MsgEnv *message_envelope)
{
	int code;
	k_atomic(1);
	code = k_get_trace_buffers(message_envelope);	
	k_atomic(0);
	return code;
}

int MsgEnv_queue_is_empty(MsgEnv_queue_ptr MQ)
{
	int code;
	k_atomic(1);
	code = k_message_queue_is_empty(MQ);
	k_atomic(0);
	return code;
}

void MsgEnv_queue_enqueue(MsgEnv *message, MsgEnv_queue_ptr MQ) 
{
	k_atomic(1);
	k_message_queue_enqueue(message, MQ);
	k_atomic(0);
	return;
}

MsgEnv *MsgEnv_queue_dequeue(MsgEnv_queue_ptr MQ)
{
	MsgEnv *msg;
	k_atomic(1);
	msg = k_message_queue_dequeue(MQ);
	k_atomic(0);
	return msg;
}
/*************************
* Timing primitives 
*************************/
int request_delay(int time_delay, int wakeup_code, MsgEnv *message_envelope)
{
	int code;
	k_atomic(1);
	code = k_request_delay(time_delay, wakeup_code, message_envelope);
	k_atomic(0);
	return code;
}

/*************************
* IO primitives 
*************************/
int send_console_chars(MsgEnv *message_envelope)
{
	int code;
	k_atomic(1);
	code = k_send_console_chars(message_envelope);
	k_atomic(0);
	return code;
}

int get_console_chars(MsgEnv *message_envelope)
{
	int code;
	k_atomic(1);
	code = k_get_console_chars(message_envelope);
	k_atomic(0);
	return code;
}
