#ifndef K_SCHEDULER_H
#define K_SCHEDULER_H

#include <setjmp.h>
#include "k_pcb.h"
#include "k_queue.h"
#include "k_priority_queue.h"
#include "k_globals.h"

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

/*************************
* Function Declarations
*************************/
void k_process_switch( );

void k_context_switch (k_PCB_ptr prev_process, k_PCB_ptr next_process);

void k_release_process (k_PCB_ptr prev_process, k_PCB_ptr next_process);

void k_change_priority (int new_priority, int target_pid);

#endif
