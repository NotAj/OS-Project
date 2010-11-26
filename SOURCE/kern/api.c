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
	//atomic(on);
	code = k_release_processor();
	//atomic(off);
	return code;	
}

int request_process_status(MsgEnv *msg_env_ptr)
{
	return 1;
}

int terminate()
{
	//atomic(on);
	k_terminate(ERROR_NONE);
	//atomic(off);
	// Should never return since terminate kills the process. Return to stop compile warnings
	return 0;
}

// Terminate function for handling all non-user shutdowns
void die(int code)
{
	//atomic(on);
	k_terminate(code);
	//atomic(off);
}

int change_priority(int new_priority, int target_process_id)
{
	int code;
	//atomic(on);
	code = k_change_priority(new_priority, target_process_id);
	//atomic(off);
	return code;
}

/*************************
* IPC primitives 
*************************/
int send_message(int dest_process_id, MsgEnv *msg_envelope)
{
	int code;
	//atomic(on);
	code = k_send_message(dest_process_id, msg_envelope);
	//atomic(off);
	return code;
}

MsgEnv *receive_message()
{
	MsgEnv *msg;
	//atomic(on);
	msg = k_receive_message();
	//atomic(off);return NULL;
	return msg;
}

int release_msg_env(MsgEnv *msg_env_ptr)
{
	int code;
	//atomic(on);
	code = k_release_msg_env(msg_env_ptr);
	//atomic(off);
	return code;
}

MsgEnv *request_msg_env()
{
	MsgEnv *msg;
	//atomic(on);
	msg = k_request_msg_env();
	//atomic(off);
	return msg;
}

int get_trace_buffers(MsgEnv *message_envelope)
{
	return 1;
}

MsgEnv_queue_ptr MsgEnv_queue_init()
{
	MsgEnv_queue_ptr messageQ;
	//atomic(on);
	messageQ = k_message_queue_init();
	//atomic(off);
	return messageQ;
}

int MsgEnv_queue_is_empty(MsgEnv_queue_ptr MQ)
{
	int code;
	//atomic(on);
	code = k_message_queue_is_empty(MQ);
	//atomic(off);
	return code;
}

void MsgEnv_queue_enqueue(MsgEnv *message, MsgEnv_queue_ptr MQ) 
{
	//atomic(on);
	k_message_queue_enqueue(message, MQ);
	//atomic(off);
	return;
}

MsgEnv *MsgEnv_queue_dequeue(MsgEnv_queue_ptr MQ)
{
	MsgEnv *msg;
	//atomic(on);
	msg = k_message_queue_dequeue(MQ);
	//atomic(off);
	return msg;
}
/*************************
* Timing primitives 
*************************/
int request_delay(int time_delay, int wakeup_code, MsgEnv *message_envelope)
{
	return 1;
}

/*************************
* IO primitives 
*************************/
int send_console_chars(MsgEnv *message_envelope)
{
	int code;
	//atomic(on);
	code = k_send_console_chars(message_envelope);
	//atomic(off);
	return code;
}

int get_console_chars(MsgEnv *message_envelope)
{
	int code;
	//atomic(on);
	code = k_get_console_chars(message_envelope);
	//atomic(off);
	return code;
}
