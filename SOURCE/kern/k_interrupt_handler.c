#include "k_defines.h"
#include "k_globals.h"
#include "k_scheduler.h"
#include "k_utility.h"
#include "k_interrupt_handler.h"
#include "k_pcb.h"

#include <signal.h>
#include <stdio.h>

void atomic(int on)
{
	static sigset_t oldmask;
	sigset_t newmask;
	//Only mask signals if flag cleared
	if (k_atomic_flag == 0 && on) 
	{
		//Set the atomic flag
		k_atomic_flag = 1;
		//Block the signals
		sigemptyset(&newmask);
		sigaddset(&newmask, SIGALRM); //the alarm signal
		sigaddset(&newmask, SIGUSR1); // the KB signal
		sigaddset(&newmask, SIGUSR2); // the CRT signal
		sigprocmask(SIG_BLOCK, &newmask, &oldmask);
	}
	//Only unmask signals if flag set
	else if (k_atomic_flag == 1)
	{
		//Clear the atomic flag
		k_atomic_flag = 0;
		//Unblock the signals
		sigprocmask(SIG_SETMASK, &oldmask, NULL);
	}
}

void k_interrupt_handler (sig_no)
{
	extern k_PCB_ptr k_current_process;
	extern k_PCB_ptr k_interrupted_process;
	atomic(1);
	switch(sig_no) 
	{
		case (SIGALRM): // Context switch to timeout iprocess 
 			k_interrupted_process = k_current_process;			
			k_context_switch(k_current_process, k_pid_to_PCB_ptr(PID_I_TIMER));
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
	atomic(0);	
	// Setting k_current_process is handled by context switching back here
}
