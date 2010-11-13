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


int i;
k_PCB_ptr pcb,pcb2, pcb3;
extern k_priority_queue_ptr k_readyPQ;
extern k_priority_queue_ptr k_blockedPQ;

void proc_1()
{
	while(1)
	{
		printf("Test context switch");
		// Test context switching outside of scheduler.
		assert(i==1);
		assert(k_current_process == pcb);
		i=2;
		k_context_switch(pcb, pcb2); // Should switch to 2
		assert(i==4);		
		assert(k_current_process == pcb);
		// Done testing context switch. 
		printf("---->PASS\n");
		// Test process switch with 3 proc, 1 is lower priority
		printf("Testing process switch");
		i = 5;
		k_current_process->p_status = STATUS_READY;
		k_priority_queue_enqueue(k_current_process, k_readyPQ);
		k_process_switch(); // Should switch to process 3
		assert(i==6);		
		assert(k_current_process == pcb);
		assert(pcb->p_status == STATUS_EXECUTING);
		printf("---->PASS\n");
		// At this point only 2 processes in readyPQ (1 is executing)	
		// Remove process 2 and 3, context switch to 2 and test only 1 process case
		printf("Testing release processor");
		k_priority_queue_remove(3, k_readyPQ);
		k_priority_queue_remove(2, k_readyPQ);
		k_current_process = pcb2;
		pcb2->p_status = STATUS_EXECUTING;
		i = 7;
		k_context_switch(pcb,pcb2);
		assert(i==12);
		// All Processes have same priority
		assert(pcb->p_priority == 3);
		assert(pcb2->p_priority == 3);
		assert(pcb3->p_priority == 3);
		// Change priority of proc3 to 1, should switch to 3
		k_change_priority(1,3);	
		i=13;
		k_release_processor();
		exit(0);
	}
}

void proc_2()
{
	while(1)
	{
		assert(i==2);
		assert(k_current_process == pcb2);
		i=3;
		k_context_switch(pcb2, pcb3); // Should switch to 3
		// At this point, readyPQ is empty, executing process is 2;
		assert(i==7);
		assert(k_current_process == pcb2);
		assert(pcb2->p_status == STATUS_EXECUTING);
		// Testing process_switch with 1 process case is same as testing release processor with 1 process case, do that
		i=8;
		k_release_processor();
		assert(i==8);
		assert(k_current_process == pcb2);
		assert(pcb2->p_status == STATUS_EXECUTING);
		// Release processor works, test change priority
		printf("---->PASS\n");
		printf("Testing change priority");
		pcb->p_priority = 3;
		pcb3->p_priority = 3;
		k_priority_queue_enqueue(pcb, k_readyPQ);
		k_priority_queue_enqueue(pcb3, k_readyPQ);
		// 1 and 3 now have priority 3, 2 has priority 2	
		// Call change_priority with invalid parameters, verify nothing happened.
		k_change_priority(1, 4); // Change pid 4 to priority 1		
		i = 9;
		k_release_processor();
		assert(i==9);
		assert(k_current_process == pcb2);
		assert(pcb2->p_status == STATUS_EXECUTING);
		k_change_priority(-1,2); // Change pid 2 to priority -1 
		i = 10;
		k_release_processor();
		assert(i==10);
		assert(k_current_process == pcb2);
		assert(pcb2->p_status == STATUS_EXECUTING);
		k_change_priority(4,2); // Change pid 2 to priority 4 
		i = 11;
		k_release_processor();
		assert(i==11);
		assert(k_current_process == pcb2);
		assert(pcb2->p_status == STATUS_EXECUTING);
		assert(pcb->p_priority == 3);
		assert(pcb2->p_priority == 2);
		assert(pcb3->p_priority == 3);
		assert(k_readyPQ->array[3]->head == pcb);
		assert(k_readyPQ->array[3]->tail == pcb3);
		// Change priority of proc 2 to 3 and process switch, should switch to 1 (Since at start of priority 3 queue)
		k_change_priority(3,2);
		i=12;

		k_release_processor();	
		exit(0);
	}
}

void proc_3()
{
	while(1)
	{
		assert(i==3);
		assert(k_current_process == pcb3);
		i=4;
		k_context_switch(pcb3,pcb); // Should switch to 1
		assert(i==5);	
		assert(k_current_process == pcb3);
		assert(pcb3->p_status == STATUS_EXECUTING);
		i=6;
		k_current_process->p_status = STATUS_READY;
		k_priority_queue_enqueue(k_current_process, k_readyPQ);
		k_process_switch(); // Should switch back to 1
		// Just got here from 1, at this point 2,1 are in PQ[3]
		assert(i==13);
		assert(pcb->p_priority == 3);
		assert(pcb2->p_priority == 3);
		assert(pcb3->p_priority == 1);
		// Change status of 3 to 3, should not affect anything, since system is non-preemptive
		k_change_priority(3,3);
		assert(pcb3->p_priority==3);
		assert(pcb3->p_status == STATUS_EXECUTING);
		assert(k_current_process == pcb3);
		// This primitive can never run while 3 is interrupted unless called from iprocess (will not happen), so ignore that case.
		// Assume 3 is blocked, change priority should just change priority value.
		pcb3->p_status = STATUS_BLOCKED_ON_RECEIVE;
		k_change_priority(2,3);
		assert(pcb3->p_priority==2);
		assert(pcb3->p_status == STATUS_BLOCKED_ON_RECEIVE);
		pcb3->p_status = STATUS_BLOCKED_ON_RESOURCE;
		k_priority_queue_enqueue(pcb3, k_blockedPQ);
		k_change_priority(1,3);
		assert(pcb3->p_priority==1);
		assert(k_blockedPQ->array[1]->head == pcb3);
		assert(pcb3->p_status == STATUS_BLOCKED_ON_RESOURCE);
		assert(pcb->p_priority == 3);
		assert(pcb2->p_priority == 3);
		assert(k_readyPQ->array[3]->head == pcb2);
		assert(k_readyPQ->array[3]->tail == pcb);
		//TODO add handling for ready or blocked_on_resource pcb not on respective queue
		printf("---->PASS\n");
		printf("SCHEDULER PASSED\n\n");
		exit(0);	
	}
}

int main()
{
	printf("TESTING SCHEDULER\n");
	int j;

	// Initialize structures;
	k_global_init();
	k_scheduler_init();
	k_ipc_init(10);	
	
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
	priority[1] = 2;
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

