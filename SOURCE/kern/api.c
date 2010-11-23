#include "k_api.h"

/****************************************************************
 User API
 ----------------------------------------------------------------
 This file has all the user visible API function available to 
 user processes. These primitives disable interrupts, then call the 
 kernel version of these primitives. They reenable interrupts before
 returning.  

*****************************************************************/
/*************************
* Scheduler primitives 
*************************/
int release_processor()
{
	//atomic(on);
	k_release_processor();
	//atomic(off);
	
}

int request_process_status(MsgEnv *msg_env_ptr)
{}

int terminate()
{}

int change_priority(int new_priority, int target_process_id)
{
	//atomic(on);
	return (k_change_priority(new_priority, target_process_id));
	//atomic(off);
}

/*************************
* IPC primitives 
*************************/
int send_message(int dest_process_id, MsgEnv *msg_envelope)
{}

MsgEnv *receive_message()
{}

MsgEnv *request_msg_env()
{}

int release_msg_env(MsgEnv *msg_env_ptr)
{}

int get_trace_buffers(MsgEnv *message_envelope)
{}

/*************************
* Timing primitives 
*************************/
int request_delay(int time_delay, int wakeup_code, MsgEnv *message_envelope)
{}

/*************************
* IO primitives 
*************************/
int send_console_chars(MsgEnv *message_envelope)
{}

int get_console_chars(MsgEnv *message_envelope)
{}

