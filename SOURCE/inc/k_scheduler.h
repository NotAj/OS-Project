#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <setjmp.h>
#include "pcb.h"
#include "queue.h"
#include "priority_queue.h"

/****************************************************************
 Scheduler
 ----------------------------------------------------------------
 The scheduler consists of the functions that perform the scheduling, 
 as well as the data structures that make it up. 
 Only the release_processor functionality is made available to processes
 via the api. 
 Iprocesses can access these functions and call scheduling functions directly. 

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
void k_process_switch( );

void k_context_switch (k_PCB_ptr prev_process, k_PCB_ptr next_process);

#endif
