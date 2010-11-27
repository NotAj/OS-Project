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
	extern int k_atomic_count;
	// If calling atomic on
	if (on)
	{
		//Only mask signals if count is 0
		if (k_atomic_count  == 0) 
		{
			// Increment the atomic count
			k_atomic_count++;
			// Block the signals
			sigemptyset(&newmask);
			sigaddset(&newmask, SIGALRM);	//the alarm signal
			sigaddset(&newmask, SIGUSR1); 	// the KB signal
			sigaddset(&newmask, SIGUSR2); 	// the CRT signal
			sigprocmask(SIG_BLOCK, &newmask, &oldmask);
		}
		else // If count > 0 
		{
			k_atomic_count++; // Just increment count
		}
	}
	// If calling atomic off
	else
	{
		if (k_atomic_count == 1)
		{
			// Decrement the atomic count
			k_atomic_count--;
			// Unblock the signals
			sigprocmask(SIG_SETMASK, &oldmask, NULL);
		} 
		else // If atomic count > 1
		{
			k_atomic_count--; // Otherwise just decrement
		}
	} 
	if (k_atomic_count < 0)
		die(ERROR_CRITICAL);
}

void k_interrupt_handler (sig_no)
{
	printf("here\n");
	extern k_PCB_ptr k_current_process;
	extern k_PCB_ptr k_interrupted_process;
 	k_interrupted_process = k_current_process;			
	atomic(1);
	switch(sig_no) 
	{
		case (SIGALRM): // Context switch to timeout iprocess 
			k_context_switch(k_current_process, k_pid_to_PCB_ptr(PID_I_TIMER));
			break;

		case (SIGUSR1): // Context switch to kbd iprocess 
			k_context_switch(k_current_process, k_pid_to_PCB_ptr(PID_I_KB));
			break;

		case (SIGUSR2): // Context switch to crt iprocess 	
			k_context_switch(k_current_process, k_pid_to_PCB_ptr(PID_I_CRT));
			break;
	}
	atomic(0);	
	// Setting k_current_process is handled by context switching back here
}
