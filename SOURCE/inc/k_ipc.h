#ifndef K_IPC_H
#define K_IPC_H

#include "k_message.h"
#include "k_pcb.h"
#include "k_message_queue.h"
#include "k_scheduler.h"
#include "k_tracebuffer.h"
#include "k_defines.h"
#include "k_utility.h"

/****************************************************************
 Queue Data structure
 ----------------------------------------------------------------
 These functions provide functionality to the IPC. It allows for 
 processes to send, receive, request and release message envelopes.

*****************************************************************/

/*************************
* Function Declarations
*************************/
int k_send_message (int dest_process_id, MsgEnv * msg_env_ptr);

MsgEnv* k_receive_message ();

MsgEnv* k_request_msg_env ();

int k_release_msg_env (MsgEnv * msg_env_ptr); 

#endif
