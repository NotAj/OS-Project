#include "k_scheduler.h"

/****************************************************************
 Scheduler
 ----------------------------------------------------------------
 The scheduler consists of the pcb, queue and priority_queue data
 structures. It serves to consolidate all the includes so that the
 api functions only need to include the scheduler. IT MIGHT BECOME
 A STRUCT WITH A GLOBAL INSTANCE THAT HAS BOTH SCHEDULING QUEUES.

*****************************************************************/

/****************************************************************************
* Function      : k_process_switch 
******************************************************************************
* Description   : 
*           
* Assumptions   : Assumes a valid queue is specified. 
*****************************************************************************/
void k_process_switch( );
{
	PCB_ptr prev_process, next_process;
	prev_process = k_current_process;
	// Retrieve next process to be run from readyQ priority queue
	next_process = k_priority_queue_dequeue(k_readyQ);	

	// Since call to context_switch results in transferring control to different process, set status of next process here, and update current_process global
	next_process->p_status = STATUS_EXECUTING;
	current_process = next_process;
	//Perform the context switch
	context_switch(prev_process, next_process);
	//At this point process has returned from having context restored, so no action necessary. Just exit function.

}

/****************************************************************************
* Function      : k_context_switch 
******************************************************************************
* Description   :
* 
* Assumptions   : Assumes a valid queue is specified. 
*****************************************************************************/
void k_context_switch (k_PCB_ptr prev_process, k_PCB_ptr next_process);
{
	int status;
	// Save the context of the previous process.
	status = set_jmp(prev_process->k_jmp_buf);
	if (status == 0) // Status is 0, signifying that context has just been saved
	{
		longjmp(next_process->jmp_buf); // Restores next_process’ context
	}
	// Function is here if returning from long_jmp(), no action required.
}

/****************************************************************************
* Function      : k_release_processor 
******************************************************************************
* Description   :
* 
* Assumptions   : Assumes a valid queue is specified. 
*****************************************************************************/
void k_release_processor (k_PCB_ptr prev_process, k_PCB_ptr next_process);
{
	// Set the process' status to ready, and enqueue to ready queue
	k_current_process->p_status == STATUS_READY;  
	k_priority_queue_enqueue(current_process, k_readyQ);
	
	//Perform a process switch
	process_switch();
}
/****************************************************************************
* Function      : k_change_priority 
******************************************************************************
* Description   : This function changes the priority of the process with the 
*				: pid specified. If the process is executing, blocked or interrupted
*				: no action is necessary. If the process is ready, it will lose it's
*				: place in the readyQ and be placed at the end of the correct 
*				: queue in the priority Q 
* 
* Assumptions   : In the case of invalid parameters, no action is taken. 
*****************************************************************************/
void k_change_priority(int new_priority, int target_pid);
{
	// Check if new priority is valid
	if (new_priority < 0 || new_priority > 3)
		return; // Do nothing

	// Get the PCB of target process.
	changed_pcb = pid_to_PCB_ptr(target_pid);
	if (changed_pcb == NULL) // Means target_pid specified is invalid
		return; // Do nothing 

	// Check if new priority specified equals old priority
	if(changed_pcb->p_priority == new_priority)
		return; // No action required

	// Check if target process is in readyQ
	if (changed_pcb->p_status == STATUS_READY)
		// Remove process from current spot in the readyQ
		changed_pcb  = k_priority_queue_remove(target_pid, k_readyQ);
		// Change the priority of target process
		changed_pcb->p_prioirity->p_priority = new_priority;
		// Enqueue onto readyQ
		k_priority_queue_enqueue(changed_pcb, k_readyQ);

	// If process is blocked, executing or interrupted, just change priority 
	changed_pcb->p_prioirty == new_priority	
	
	return 1;
}

/****************************************************************************
* Function      : k_context_switch 
******************************************************************************
* Description   :
* 
* Assumptions   : Assumes a valid queue is specified. 
*****************************************************************************/
void k_context_switch (k_PCB_ptr prev_process, k_PCB_ptr next_process);
{
