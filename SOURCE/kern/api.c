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
	return 1;
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
	return 1;
}

MsgEnv *receive_message()
{
	return NULL;
}

int release_msg_env(MsgEnv *msg_env_ptr)
{
	return 1;
}

int get_trace_buffers(MsgEnv *message_envelope)
{
	return 1;
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
	return 1;
}

int get_console_chars(MsgEnv *message_envelope)
{
	return 0;
}
