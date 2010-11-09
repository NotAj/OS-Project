#ifndef MESSAGE_QUEUE_H
#define MESSAGE_QUEUE_H

#include <stdlib.h>
#include "message.h"

/****************************************************************
 Message Queue Data Structure 
 ----------------------------------------------------------------
 This structure is used for the received messages queue inside each
 PCB. The functions are almost identical to the queue structure,
 but they deal with message envelope pointers instead of PCB pointers.

*****************************************************************/

/*************************
* Type Declarations
*************************/
typedef struct k_message_queue_struct *k_message_queue_ptr;

typedef struct k_message_queue_struct
{	
	MsgEnv_ptr head;
	MsgEnv_ptr tail;
} k_message_queue;

/*************************
* Function Declarations
*************************/
int k_message_queue_is_empty (k_message_queue_ptr MQ);

void k_message_queue_enqueue (MsgEnv_ptr message, k_message_queue_ptr MQ);

MsgEnv_ptr k_message_queue_dequeue (k_message_queue_ptr MQ);

#endif
