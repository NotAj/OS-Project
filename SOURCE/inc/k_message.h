#ifndef K_MESSAGE_H
#define K_MESSAGE_H

#include "k_defines.h"

/****************************************************************
 Message Envelope Data structure
 ----------------------------------------------------------------
 This structure is used for all interprocess communication. Message
 Envelopes are passed back and forth between process to exchange 
 information, and to send/receive IO. For this IPC scheme it is 
 assumed that all processes know each others PID. 
 The message envelope structure contains the PID of the sender 
 and receiver and the message type. These help the receiving 
 processes figure out what to expect in the message, or know
 what process to reply to. The expiry_time field is used by
 the timer i-process and processes requesting a delay. The
 msg_size field is used to simplify reading the message contents,
 which are stored in an array of characters.

*****************************************************************/

/*************************
* Type Declarations
*************************/
typedef struct k_message_struct *k_message_ptr;

typedef struct k_message_struct
{	
	k_message_ptr k_queue_next;
	int sender_pid;
	int receiver_pid;
	int msg_type;
	int expiry_time;
	int msg_size;
	char msg_text[MSG_ENV_SIZE];
} MsgEnv;

typedef struct k_message_struct k_message;

/*************************
* Function Declarations
*************************/
#endif
