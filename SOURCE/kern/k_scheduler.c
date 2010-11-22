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
* Description   : This function is called by any functions that need to change
*				: processes using the scheduler. It retrieves the ready process
*				: with the highest priority from the readyQ, updates the 
*				: current_process global, sets it to executing, and does a context
*				: switch. This function is called by release_processor, 
*				: receive_message and request_msg_env functions.
*           
* Assumptions   : This function assumes previously executing process has already
*				: been set to ready/blocked and enqueued on the appropriate queue 
*				: Assumes that there is always a ready process on the readyQ 
*****************************************************************************/
void k_process_switch ( )
{
	extern k_PCB_ptr k_current_process;
	extern k_priority_queue_ptr k_readyPQ;

	k_PCB_ptr prev_process, next_process;
	prev_process = k_current_process;
	// Retrieve next process to be run from readyQ priority queue
	next_process = k_priority_queue_dequeue(k_readyPQ);	

	// Since call to context_switch results in transferring control to different process, set status of next process here, and update current_process global
	next_process->p_status = STATUS_EXECUTING;
	k_current_process = next_process;
	//Perform the context switch
	k_context_switch(prev_process, next_process);
	//At this point process has returned from having context restored, so no action necessary. Just exit function.
}

/****************************************************************************
* Function      : k_context_switch 
******************************************************************************
* Description   : This function only saves the context of prev_process and 
*				: restores the context of next_process. It is called by process
*				: switch to perform the context switching, or called directly by
*				: the signal handler to perform context switching to an iprocess 
*				: outside of the scheduler.
* 
* Assumptions   : Assumes all system variables have been updated prior to being 
*				: called to ensure proper system operation. 
******************************************&**********************************/
void k_context_switch (k_PCB_ptr prev_process, k_PCB_ptr next_process)
{
	//TODO Deal with commented printf
	//int status;
	// Save the context of the previous process.
	//status = setjmp(prev_process->k_jmp_buf);
	//printf("SWITCH PID %d->%d\n", prev_process->p_pid, next_process->p_pid);
	//printf("STATUS = %d\n", status);
	//if (status == 0) // Status is 0, signifying that context has just been saved
	if(setjmp(prev_process->k_jmp_buf) == 0)
	{
		//printf("JUMP %d->%d\n", prev_process->p_pid, next_process->p_pid);
		longjmp(next_process->k_jmp_buf, 1); // Restores next_process’ context
	}
	//printf("RESTORED %d->%d\n", prev_process->p_pid,next_process->p_pid);
	// Function is here if returning from long_jmp(), no action required.
}

/****************************************************************************
* Function      : k_release_processor 
******************************************************************************
* Description   : This function is used by an executing process to stop execution
*				: and switch to the next ready process. 
* 
* Assumptions   : 
*****************************************************************************/
void k_release_processor (k_PCB_ptr prev_process, k_PCB_ptr next_process)
{
	extern k_PCB_ptr k_current_process;	
	extern k_priority_queue_ptr k_readyPQ;

	// Set the process' status to ready, and enqueue to ready queue
	k_current_process->p_status = STATUS_READY;  
	k_priority_queue_enqueue(k_current_process, k_readyPQ);
	
	//Perform a process switch
	k_process_switch();
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
void k_change_priority(int new_priority, int target_pid)
{
	extern k_priority_queue_ptr k_readyPQ;

	k_PCB_ptr changed_pcb;

	// Check if new priority is valid
	if (new_priority < 0 || new_priority > 3)
		return; // Do nothing

	// Get the PCB of target process.
	changed_pcb = k_pid_to_PCB_ptr(target_pid);
	if (changed_pcb == NULL) // Means target_pid specified is invalid
		return; // Do nothing 

	// Check if new priority specified equals old priority
	if(changed_pcb->p_priority == new_priority)
		return; // No action required

	// Check if target process is in readyQ
	if (changed_pcb->p_status == STATUS_READY)
		// Remove process from current spot in the readyQ
		changed_pcb  = k_priority_queue_remove(target_pid, k_readyPQ);
		// Change the priority of target process
		changed_pcb->p_priority = new_priority;
		// Enqueue onto readyQ
		k_priority_queue_enqueue(changed_pcb, k_readyPQ);

	// If process is blocked, executing or interrupted, just change priority 
	changed_pcb->p_priority = new_priority;	
	
	return;
}

