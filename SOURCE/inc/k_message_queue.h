#ifndef K_MESSAGE_QUEUE_H
#define K_MESSAGE_QUEUE_H

#include <stdlib.h>
#include "k_message.h"

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
	k_message_ptr head;
	k_message_ptr tail;
} k_message_queue;

typedef struct k_message_queue_struct MsgEnv_queue;

typedef struct k_message_queue_struct *MsgEnv_queue_ptr;


/*************************
* Function Declarations
*************************/
int k_message_queue_is_empty (k_message_queue_ptr MQ);

void k_message_queue_enqueue (k_message_ptr message, k_message_queue_ptr MQ);

k_message_ptr k_message_queue_dequeue (k_message_queue_ptr MQ);

#endif
