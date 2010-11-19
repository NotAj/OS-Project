#include "k_utility.h"

/****************************************************************
 Utility Functions
 ----------------------------------------------------------------
 This file contains all the utility functions that are needed for
 the user api, or for use in other functions 
*****************************************************************/

/***************************************************************************
* Function      : pid_to_PCB_ptr 
****************************************************************************
* Description   : This function takes a PID and returns a pointer to the PCB
*				: of the corresponding process. 
*              
* Assumptions   : Will return NULL if PCB with that PID doesn't exist.
*****************************************************************************/
k_PCB_ptr k_pid_to_PCB_ptr (int pid)
{
	k_PCB_ptr pcb;
	extern k_queue_ptr k_allQ;
	pcb = k_allQ->head;
	// Iterate through queue until PCB with pid is found.
	while (pcb != NULL && pcb->p_pid != pid)
		pcb = pcb->k_queue_next;
	// If here, pcb either has pointer to process with correct PID or is NULL
	// In either case, return pcb
	return pcb;
}

