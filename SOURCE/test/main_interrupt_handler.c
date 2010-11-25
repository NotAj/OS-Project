#include "k_queue.h"
#include "k_pcb.h"
#include "k_priority_queue.h"
#include "k_itable.c"
#include "k_scheduler.h"
#include "test_queue.h"
#include "test_priority_queue.h"
#include "k_init_struct.h"
#include "k_init.h"
#include "k_globals.h"
#include "k_ipc.h"
#include "k_interrupt_handler.h"
#include <signals.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/wait.h>

int main()
{
	sigset (SIGALRM, interrupt_handler(14)); //linux clock signal
	sigset (SIGUSR1, interrupt_handler(30)); //keyboard helper signal
	sigset (SIGUSR2, interrupt_handler(31)); //crt helper signal
	ualarm (1, 1);	//sets a SIGALRM to be fired everY time interval
	int parent_pid = get_pid();	
	int newPID = fork();
	if(newPID == 0)		
	{
		kill(parent_pid, SIGUSR1); 
		kill(parent_pid, SIGUSR2); 
	}
	wait(-1);
}
