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

	switch(sig_no) 
	{
	case (SIGALRM): 	k_interrupted_process = k_current_process;
				k_context_switch(k_current_process, pid_to_PCB_ptr(PID_I_TIMER));
				break;

	case (SIGUSR1): 	k_interrupted_process = k_current_process;
				k_context_switch(k_current_process, pid_to_PCB_ptr(PID_I_KB));
				break;

	case (SIGUSR2): 	k_interrupted_process = k_current_process;
				k_context_switch(k_current_process, pid_to_PCB_ptr(PID_I_CRT));
				break;
	}
}
