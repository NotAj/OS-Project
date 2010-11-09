#ifndef QUEUE_H
#define QUEUE_H

#include "pcb.h"

/****************************************************************
 Queue Data structure
 ----------------------------------------------------------------
 This structure is used for the allQ which contains all processes 
 in the RTX.
 It is also used inside the Priority Queue structure, which is an
 array of these queues. The readyQ and blockedQ are examples of 
 these. 

*****************************************************************/

/*************************
* Type Declarations
*************************/
typedef struct k_queue_struct *k_queue_ptr;

typedef struct k_queue_struct
{	
	k_PCB_ptr head;
	k_PCB_ptr tail;
} k_queue;

/*************************
* Function Declarations
*************************/
int k_queue_is_empty (k_queue_ptr Q);

void k_queue_enqueue (k_PCB_ptr process, int all_Q, k_queue_ptr Q);

k_PCB_ptr k_queue_dequeue (k_queue_ptr Q);

k_PCB_ptr k_queue_remove(int PID, k_queue_ptr Q);

#endif
