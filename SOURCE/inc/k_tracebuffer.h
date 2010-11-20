#ifndef K_TRACEBUFFER_H
#define K_TRACEBUFFER_H

#include <stdlib.h>
#include "k_defines.h"

/****************************************************************
 Tracebuffer Data Structure 
 ----------------------------------------------------------------
 This structure is used to trace the sending and receiving of 
 messages between processes. The tracebuffer contains the PID of
 the sender and receiver, as well as the type of message and the 
 system time at which it was sent or received. This functionality 
 is included in the send_message and receive_message functions,
 and the information is printed by the get_tracebuffer function.

*****************************************************************/

/*************************
* Type Declarations
*************************/
typedef struct k_trace_struct *k_trace_ptr;

typedef struct k_trace_struct
{
	int sender_pid;
	int receiver_pid;
	int msg_type;
	int timestamp;
} k_trace;

typedef struct k_tracebuffer_struct *k_tracebuffer_ptr;

typedef struct k_tracebuffer_struct
{
	k_trace_ptr buffer[TRACEBUFFER_SIZE];
	int head;
	int tail;
} k_tracebuffer;


/*************************
* Function Declarations
*************************/
void k_tracebuffer_update (int sender_pid, int receiver_pid, int msg_type, k_tracebuffer_ptr TB);

#endif
