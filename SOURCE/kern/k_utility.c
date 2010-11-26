#include "k_utility.h"

/****************************************************************
 Utility Functions
 ----------------------------------------------------------------
 This file contains all the utility functions that are needed for
 the user api, or for use in other functions 
*****************************************************************/

/***************************************************************************
* Function      : k_terminate 
****************************************************************************
* Description   : This function performs cleanup, then terminates the OS
*				: It deletes the shared memory files, kills the child processes
*				: then exits the OS, printing the reason why terminate was called
*              
* Assumptions   : Will return NULL if PCB with that PID doesn't exist.
*****************************************************************************/
void k_terminate(int error)
{
	extern int k_kbd_helper_pid;
	extern int k_crt_helper_pid;
	extern int k_inputfile_fid;
	extern int k_outputfile_fid;
	extern char *k_inputfile_path;
	extern char *k_outputfile_path;

	// Kill helper processes
	kill(k_kbd_helper_pid, SIGKILL); //send a kill signal to kb helper 
	kill(k_crt_helper_pid, SIGKILL); //send a kill signal to crt helper

	// Clean shared memory 
	// Close both mmaped files
	close(k_inputfile_fid);
	close(k_outputfile_fid);
		
	// Unlink (delete) both mmap files
	unlink(k_inputfile_path);
	unlink(k_outputfile_path);

	//Stop RTX Execution and return control to UNIX
	exit(0);	
}

/***************************************************************************
* Function      : k_request_delay 
****************************************************************************
* Description   : This function is used to send a delay request to the timer
*				: iprocess by specifying the time_delay in number of 100msec
*				: intervals. The caller can specify the wake up code that will
*				: be provided in the message type field once the delay is complete. 
*              
* Assumptions   : A valid MsgEnv * must have been previously requested and supplied.
*****************************************************************************/
k_request_delay (int time_delay, int wakeup_code, MsgEnv *message_envelope)
{
	message_envelope->msg_type = wakeup_code;
	message_envelope->expiry_time = time_delay;
	message_envelope->msg_size = 0;
	k_send_message(PID_I_TIMER, message_envelope);
	return ERROR_NONE;
}

/***************************************************************************
* Function      : k_pid_to_PCB_ptr 
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
		pcb = pcb->k_all_queue_next;
	// If here, pcb either has pointer to process with correct PID or is NULL
	// In either case, return pcb
	return pcb;
}

