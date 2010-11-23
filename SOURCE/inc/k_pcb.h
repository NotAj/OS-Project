#ifndef K_PCB_H
#define K_PCB_H

#include <stdlib.h>
#include <setjmp.h>
#include "k_message.h"
#include "k_message_queue.h"
#include "k_defines.h"

/****************************************************************
 PCB Data structure
 ----------------------------------------------------------------
 This structure contains all important information on each process
 in the RTX. A PCB for each process is created during intialization
 and is tracked on the various scheduling queues and the allQ. 
 Each PCB contains the PID, status, priority of a process. It also
 contains the stack pointer for each process, as well as a field to
 store the context when switching processes. Each process also has
 a queue of pending messages.

*****************************************************************/

/*************************
* Type Declarations
*************************/

typedef struct k_PCB_struct *k_PCB_ptr;

typedef struct k_PCB_struct 
{
	k_PCB_ptr k_queue_next;
	k_PCB_ptr k_all_queue_next;
	k_message_queue_ptr k_received_message_queue;
	int p_pid ;
	int p_priority;
	int p_status;
	void *k_stack_pointer;
	jmp_buf k_jmp_buf;
	void *k_start_address;
} k_PCB;

/*************************
* Function Declarations
*************************/
//k_PCB_ptr pid_to_PCB_ptr (int pid, k_queue_ptr Q);

#endif
