#ifndef QUEUE_H
#define QUEUE_H

#include "pcb.h"

/***************************************************
 * This is the header file for the base queue struct
***************************************************/

/* Type Declarations
 *---------------------- */

typedef struct k_queue_struct *k_queue_ptr;

typedef struct k_queue_struct
{	
	k_PCB_ptr head;
	k_PCB_ptr tail;
} k_queue;


/* Function Declarations
 *---------------------- */
int k_queue_is_empty (k_queue_ptr Q);

void k_queue_enqueue (k_PCB_ptr process, int all_Q, k_queue_ptr Q);

k_PCB_ptr k_queue_dequeue (k_queue_ptr Q);

k_PCB_ptr k_queue_remove(int PID, k_queue_ptr Q);

#endif
