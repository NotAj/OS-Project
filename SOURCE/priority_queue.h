#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "queue.h"

/***************************************************
 * This is the header file for the base queue struct
***************************************************/

/* Type Declarations
 *---------------------- */

typedef struct k_priority_queue_struct *k_priority_queue_ptr;

typedef struct k_priority_queue_struct
{	
	// Array of a type is headed by a pointer to the type, so make a pointer to a queue_ptr
	// 4 priority levels, so 4 items in the array.	
	k_queue_ptr array[4]; 
} k_priority_queue;


/* Function Declarations
 *---------------------- */
int k_priority_queue_is_empty (k_priority_queue_ptr PQ);

void k_priority_queue_enqueue (k_PCB_ptr process, k_priority_queue_ptr PQ);

k_PCB_ptr k_priority_queue_dequeue (k_priority_queue_ptr PQ);

#endif
