#ifndef API_H
#define API_H

#include "k_scheduler.h"
#include "k_ipc.h"
#include "k_init_struct.h"
#include "k_globals.h"
#include "k_defines.h"

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
int release_processor();

int request_process_status(MsgEnv *msg_env_ptr);

int terminate();

int change_priority(int new_priority, int target_process_id);

/*************************
* IPC primitives 
*************************/
int send_message(int dest_process_id, MsgEnv *msg_envelope);

MsgEnv *receive_message();

MsgEnv *request_msg_env();

int release_msg_env(MsgEnv *msg_env_ptr);

int get_trace_buffers(MsgEnv *message_envelope);

MsgEnv_queue_ptr MsgEnv_queue_init();

int MsgEnv_queue_is_empty(MsgEnv_queue_ptr MQ);

void MsgEnv_queue_enqueue(MsgEnv *message, MsgEnv_queue_ptr MQ); 

MsgEnv *MsgEnv_queue_dequeue(MsgEnv_queue_ptr MQ);

/*************************
* Timing primitives 
*************************/
int request_delay(int time_delay, int wakeup_code, MsgEnv *message_envelope);

/*************************
* IO primitives 
*************************/
int send_console_chars(MsgEnv *message_envelope);

int get_console_chars(MsgEnv *message_envelope);

#endif
