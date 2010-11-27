#ifndef TIMEOUT_QUEUE_H
#define TIMEOUT_QUEUE_H

#include <stdlib.h>
#include "k_message.h"

/****************************************************************
Timeout Queue Data Structure
----------------------------------------------------------------
This data structure is a priority queue that holds timout requests 
while they are waiting to be timed out.
*****************************************************************/

/*************************
* Type Declarations
*************************/
typedef struct k_timeout_queue_struct *k_timeout_queue_ptr;

typedef struct k_timeout_queue_struct
{
k_message_ptr head;
} k_timeout_queue;

/*************************
* Function Declarations
*************************/
void k_timeout_queue_enqueue (k_message_ptr msg, k_timeout_queue_ptr TQ);

k_message_ptr k_timeout_queue_dequeue (k_timeout_queue_ptr TQ);

#endif
