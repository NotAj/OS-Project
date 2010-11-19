#include "k_pcb.h"

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

/****************************************************************************
* Function      : pid_to_PCB_ptr 
******************************************************************************
* Description   : This function takes a PID and returns a pointer to the PCB
*				: of the corresponding process. 
*              
* Assumptions   : Will return NULL if PCB with that PID doesn't exist.
*****************************************************************************/
/*
k_PCB_ptr pid_to_PCB_ptr (int pid)
{
	k_PCB_ptr pcb;
	pcb = k_allQ->head;
	// Iterate through queue until PCB with pid is found.
	while (pcb != NULL && pcb->p_pid != pid)
		pcb = pcb->k_queue_next;
	// If here, pcb either has pointer to process with correct PID or is NULL
	// In either case, return pcb
	return pcb;
}
*/
