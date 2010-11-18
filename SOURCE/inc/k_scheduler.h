#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "pcb.h"
#include "queue.h"
#include "priority_queue.h"

/****************************************************************
 Scheduler
 ----------------------------------------------------------------
 The scheduler consists of the pcb, queue and priority_queue data
 structures. It serves to consolidate all the includes so that the
 api functions only need to include the scheduler. IT MIGHT BECOME
 A STRUCT WITH A GLOBAL INSTANCE THAT HAS BOTH SCHEDULING QUEUES.

*****************************************************************/

/*************************
* Type Declarations
*************************/
/*typedef struct k_queue_struct *k_queue_ptr;

typedef struct k_queue_struct
{	
	k_PCB_ptr head;
	k_PCB_ptr tail;
} k_queue;
*/
/*************************
* Function Declarations
*************************/
/*int k_queue_is_empty (k_queue_ptr Q);

void k_queue_enqueue (k_PCB_ptr process, int all_Q, k_queue_ptr Q);

k_PCB_ptr k_queue_dequeue (k_queue_ptr Q);

k_PCB_ptr k_queue_remove(int PID, k_queue_ptr Q);
*/
#endif
