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
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	sigset (SIGALRM, k_interrupt_handler); //linux clock signal
	printf("Sigset sigalrm \n");
	sigset (SIGUSR1, k_interrupt_handler); //keyboard helper signal
	printf("Sigset sigusr1 \n");	
	sigset (SIGUSR2, k_interrupt_handler); //crt helper signal
	printf("Sigset sigusr2 \n");		
	ualarm (10, 100000);//sets a SIGALRM to be fired every time interval
	printf("ualarm set \n");	
	int parent_pid = getpid();	
	kill(parent_pid, SIGUSR1); 
	printf("sigusr1 sent \n");
	kill(parent_pid, SIGUSR2); 
	printf("sigusr1 sent \n");
}


