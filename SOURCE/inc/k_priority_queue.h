#ifndef K_PRIORITY_QUEUE_H
#define K_PRIORITY_QUEUE_H

#include <stdlib.h>
#include "k_pcb.h"
#include "k_queue.h"
#include "k_utility.h"
#include "k_defines.h"

/****************************************************************
 Priority Queue Data structure
 ----------------------------------------------------------------
 This structure is used for the scheduling queues readyQ and 
 blockedQ. The structure is an array of queues, with each element
 in the array holding a queue for the corresponding priority. 
 PCBs are added and removed from the queue based on this priority value. 

*****************************************************************/
/***************************
* Type Declarations
****************************/

typedef struct k_priority_queue_struct *k_priority_queue_ptr;

typedef struct k_priority_queue_struct
{	
	// 4 priority levels, so 4 items in the array.	
	// Making an array of Q pointers because all Q functions operate on a k_queue_ptr
	// Because of this, the 4 queues need to be initialized and placed in the array during initialization.
	k_queue_ptr array[4]; 
} k_priority_queue;

/*************************
* Function Declarations
*************************/
int k_priority_queue_is_empty (k_priority_queue_ptr PQ);

void k_priority_queue_enqueue (k_PCB_ptr process, k_priority_queue_ptr PQ);

k_PCB_ptr k_priority_queue_dequeue (k_priority_queue_ptr PQ);

k_PCB_ptr k_priority_queue_remove (int pid, k_priority_queue_ptr PQ);

#endif
