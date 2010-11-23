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
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "test_queue.h"
#include "test_priority_queue.h"

//#define DEBUG//TODO

/****************************************************************
 Test cases 
 ----------------------------------------------------------------
 -Test context switch between processes x2
 -Test process_switch when only 1 process
 -Test process_switch when 2 processes of same priority
 -Test process_switch when have 3 processes, 1 is lower
 -Test process_switch when have  
 *****************************************************************/

// NOTE Process switch doesn't enqueue onto scheduling queues by design.


int i,j;
k_PCB_ptr pcb,pcb2, pcb3;
extern k_priority_queue_ptr k_readyPQ;
extern k_priority_queue_ptr k_blockedPQ;
extern k_message_queue_ptr k_freeQ;

void proc_1()
{
	while(1)
	{
		k_message_ptr message1; 
	
		printf("Testing Successfull Request\n");
		
		message1 = k_request_msg_env();

		assert(message1 != NULL);
		assert(i == 1);
		
		printf("---->PASS\n");
		

		printf("Testing Successfull Send\n");
		
		message1->msg_size = 3;		
		j = k_send_message(2, message1);
		
		assert(j == 1);
	
		i = 2;
		message1 = NULL;
		printf("---->PASS\n");
		k_context_switch(pcb, pcb2);

		k_release_processor();
		exit(0);
	}
}	

void proc_2()
{
	while(1)
	{
		k_message_ptr message2;
		assert(i == 2);		
		printf("Testing Successfull Receive\n");
		
		message2 = k_receive_message();
		
		assert(message2 != NULL);
		assert(i == 2);

		printf("---->PASS\n");
		
		printf("Testing Successfull Release\n");

		j = k_release_msg_env(message2);
		
		assert(i == 2);
		assert(j == 1);

		printf("---->PASS\n");

		k_release_processor();	
		exit(0);
	}
}

void proc_3()
{
	while(1)
	{
		
		exit(0);	
	}
}

int main()
{
	printf("TESTING IPC FUNCTIONS\n");
	int j;

	// Initialize structures;
	k_global_init();
printf("CHECK1");
	k_scheduler_init();
printf("CHECK2");
	k_ipc_init(10);	
printf("CHECK3");	
	int pid[3];
	int priority[3];
	int is_iprocess[3];
	void *start_address[3];

	int num_proc = 3;
	
	pid[0] = 1;
	priority[0] = 0;
	is_iprocess[0] = 0;
	start_address[0] = (void *)&proc_1;

	pid[1] = 2;
	priority[1] = 0;
	is_iprocess[1] = 0;
	start_address[1] = (void *)&proc_2;

	pid[2] = 3;
	priority[2] = 0;
	is_iprocess[2] = 0;
	start_address[2] = (void *)&proc_3;
	
	k_itable_ptr init_table;
	init_table = k_itable_init(num_proc, pid, priority, is_iprocess, start_address);
	k_process_init(num_proc, init_table);
	
	pcb = k_pid_to_PCB_ptr(1);
	pcb2 = k_pid_to_PCB_ptr(2);
	pcb3 = k_pid_to_PCB_ptr(3);
	
	i=1;
	
	k_process_switch();
}

