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

//#define DEBUG//TODO

void proc_1()
{
	while(1)
	{
		printf("Process 1\n");
		k_PCB_ptr pcb,pcb2, pcb3;
		pcb = k_pid_to_PCB_ptr(1);
		pcb2 = k_pid_to_PCB_ptr(2);
		pcb3 = k_pid_to_PCB_ptr(3);
	//	printf("proc1->%p\n",pcb->k_start_address);
	//	printf("proc1->%p\n",pcb2->k_start_address);
		
		//k_priority_queue_enqueue(pcb, k_readyPQ);
		//k_current_process = pcb3;
		k_context_switch(pcb, pcb2);
	//	k_release_processor();
	}
}

void proc_2()
{
	while(1)
	{
		printf("Process 2\n");
	//	k_release_processor();
	}
}

void proc_3()
{
	while(1)
	{
		printf("Process 3\n");
		printf("STILL Process 3\n");
	//	k_release_processor();
	}
}

int main()
{
	printf("TESTING SCHEDULER\n");
	int i, j;

	// Initialize structures;
	k_global_init();
	k_scheduler_init();
	k_ipc_init(10);	
	
	int pid[2];
	int priority[2];
	int is_iprocess[2];
	void *start_address[2];

	int num_proc = 3;
	
	pid[0] = 1;
	priority[0] = 0;
	is_iprocess[0] = 0;
	start_address[0] = (void *)&proc_1;
	printf("proc1->%p\n",&proc_1);

	pid[1] = 2;
	priority[1] = 1;
	is_iprocess[1] = 0;
	start_address[1] = (void *)&proc_2;
	printf("proc2->%p\n",&proc_2);

	pid[2] = 3;
	priority[2] = 0;
	is_iprocess[2] = 0;
	start_address[2] = (void *)&proc_3;
	printf("proc3->%p\n",&proc_3);


	//TODO allPCB = malloc(sizeof(k_PCB_ptr) * 2);
	
	k_itable_ptr init_table;
	init_table = k_itable_init(num_proc, pid, priority, is_iprocess, start_address);
	k_process_init(num_proc,init_table);
	k_process_switch();
	

/*	switch(setjmp(buf))
	{
		case(0):
			printf("Test context switch");
			pcb = k_PCB_init(0,0,0,NULL);
			pcb2 = k_PCB_init(1,1,1,NULL);
			// Context of pcb2 saved;
			if(setjmp(pcb->k_jmp_buf))
			{	
				// Here pcb has been restored, i should still be zero
				assert(i == 0);
				i++; // Incrementing i
				printf("Before\n");
				k_context_switch(pcb, pcb2); // Restore context of pcb2 
				printf("After\n");
				// Should never come back here
				assert(0);
			}
			else // Here after saving context of pcb, i set to 10
				i = 0;
			// Restoring context of pcb, i should not be incremented 
			k_context_switch(pcb2, pcb); 	
			i++; // Incrementing i, should be 2 at this point (since incremented in pcb2)
			// Here if context of pcb is restored, i should equal 2
			assert(i == 2);
			// Done setjmp test, go back to start
			printf("---->PASS\n");
			longjmp(buf,1);	
		default:
			printf("PASSED\n");	
			break;
	}

	for (i=0; i<3;i++)
	{
		for(j=0; j<4;j++)
		{
		pcb = k_PCB_init(j*10 + i,STATUS_READY,j,NULL);
		k_priority_queue_enqueue(pcb, k_readyPQ);
		}
	}
	k_current_process = k_PCB_init(23, STATUS_EXECUTING, 2, NULL); 
	// At this point readyQ has 12 processes.
	// One executing process of priority 2. 
	// priority_queue test function has already tested the queue functionality
	// Need to test the functionality of the block and all functions here.  
	printf("Test process switch\n"); 
*/
}

