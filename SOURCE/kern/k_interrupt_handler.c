#include "k_defines.h"
#include "k_globals.h"
#include "k_scheduler.h"
#include "k_interrupt_handler.h"
#include <signal.h>
#include <stdio.h>

void k_interrupt_handler (sig_no)
{
	extern k_PCB_ptr k_current_process;
	extern k_PCB_ptr k_interrupted_process;
	//atomic(on);
	switch(sig_no) 
	{
		case (SIGALRM): // Context switch to timeout iprocess 
 			//TODO
			//k_interrupted_process = k_current_process;			
			//k_context_switch(k_current_process, k_pid_to_PCB_ptr(PID_I_TIMER));
			break;

		case (SIGUSR1): // Context switch to kbd iprocess 
	 		k_interrupted_process = k_current_process;
			k_context_switch(k_current_process, k_pid_to_PCB_ptr(PID_I_KB));
			break;

		case (SIGUSR2): // Context switch to crt iprocess 	
			k_interrupted_process = k_current_process;
			k_context_switch(k_current_process, k_pid_to_PCB_ptr(PID_I_CRT));
			break;
	}
	//atomic(off);	
	// Setting k_current_process is handled by context switching back here
}
