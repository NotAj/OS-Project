#include "k_queue.h"
#include "k_pcb.h"
#include "k_priority_queue.h"
#include "k_scheduler.h"
#include "test_queue.h"
#include "test_priority_queue.h"
#include "k_init_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "k_itable.c"


k_PCB_ptr allPCB[2];
int stop = 0;

void proc_0()
{
	int j;
	stop = 1;
	printf("In Process 0\n");
	k_context_switch(allPCB[0], allPCB[1]);
	printf("In Process 0, after context switch\n");
	
	while(1)
		j++;	
}

void proc_1()
{
	int j;
	stop = 1;
	printf("Process 1\n");
	k_context_switch(allPCB[1],allPCB[0]);
	printf("In Process 1, after context switch\n");
	while (1)
		j++;
}

int main()
{
	printf("TESTING SCHEDULER\n");
	int i, j;

	// Initialize structures;
	k_PCB_ptr pcb, pcb2;
	int results;
	jmp_buf buf;
	extern k_priority_queue_ptr k_readyPQ;
	extern k_PCB_ptr k_current_process;
	k_readyPQ = k_priority_queue_init();	
	void (*start_add[2])();
	start_add[0] = &proc_0;
	start_add[1] = &proc_1;	
	
	for(i=0;i<2;i++)
	{
		pcb = k_PCB_init(i,i,i,start_add[i]);
		pcb->k_stack_pointer = malloc(STACK_SIZE);
		allPCB[i] = pcb;
		if(!(setjmp(buf)))
		{
			if(!(setjmp(pcb->k_jmp_buf)))
			{
				printf("Set Context %d\n",i);
				longjmp(buf,1);
			}
			else
			{
				printf("First Restore %d\n",pcb->p_pid);
				void (*fp)() = pcb->k_start_address;
				fp();
				printf("AFTER FUNCTION CALL %d\n",pcb->p_pid);
			}
		}	
	}
	if (stop == 0)
	{
		k_context_switch(allPCB[0],allPCB[1]); 
		printf("AFTER FIRST CONTEXT SWITCH\n");
	}

	printf("DONE\n");


/*
	pcb = k_PCB_init(1,1,1,NULL);
	pcb2 = k_PCB_init(2,2,2,NULL);
	

	setjmp(pcb2->k_jmp_buf);
	if(!setjmp(pcb->k_jmp_buf)) {
		printf("Saved 2\n");
		//setjmp(pcb2->k_jmp_buf)
		k_context_switch(pcb2,pcb);
		printf("Restored 2\n");
	}
	else
	{
		printf("Restored 1\n");
		k_context_switch(pcb,pcb2);
	}	
	printf("TEST");
*/
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

