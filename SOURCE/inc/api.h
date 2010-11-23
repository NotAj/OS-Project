#ifndef API_H
#define API_H

#include "k_pcb.h"
#include "k_queue.h"
#include "k_priority_queue.h"
#include "k_scheduler.h"
#include "k_message.h"
#include "k_message_queue.h"
#include "k_tracebuffer.h"
#include "k_globals.h"

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