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
k_PCB_ptr pcb,pcb2,pcb3,pcb4;
extern k_priority_queue_ptr k_readyPQ;
extern k_priority_queue_ptr k_blockedPQ;
extern k_message_queue_ptr k_freeQ;

void proc_1()
{
	while(1)
	{
		k_message_ptr message1; 
/*****************************************************************/	
/*CASE 1*/	printf("TESTING SUCCESSFULL REQUEST");
		
		message1 = k_request_msg_env();

		assert(message1 != NULL);
		assert(i == 1);
		
		printf("---->PASS\n");
/*****************************************************************/
/*CASE 2*/	printf("TESTING SUCCESSFULL SEND");
		
		message1->msg_size = 3;		
		j = k_send_message(2, message1);
		
		assert(j == ERROR_NONE);
	
		i = 2;
		message1 = NULL;
		printf("---->PASS\n");
		k_release_processor();
/*****************************************************************/
/*CASE 3*/
/*****************************************************************/
/*CASE 4*/
/*****************************************************************/
/*CASE 5*/	assert(i == 5);
		printf("-->Blocked\n");
		printf("Process 1 Requesting Envelope");
		i = 6;
		message1 = k_request_msg_env();
/*****************************************************************/
/*CASE 6*/	if (i == 8)
			printf("FAIL");
/*****************************************************************/
/*CASE 7*/	assert(i == 10);
		assert(message1 != NULL);
		printf(" and Retrieved by Process 1\n");
		printf("TESTING SECOND RETURN TO READY STATE---->PASS\n\n");
/*****************************************************************/
/*CASE 8*/	printf("TESTING REBLOCK ON REQUEST:\n");		
		i = 11;
		k_release_processor();

		assert(i == 14);
		i = 15;
		k_release_processor();

		assert(i == 16);
		i = 17;
		k_release_processor();
/*****************************************************************/
/*CASE 9*/	assert(i == 19);
		i = 20;
		k_release_processor();
/*****************************************************************/
/*CASE 10*/	assert(i == 21);
		i = 22;
		j = 0;
		j = k_send_message(2, message1);
		assert(j == ERROR_NONE);
		message1 = NULL;
		k_release_processor();

		exit(0);
	}
}	

void proc_2()
{
	while(1)
	{
		k_message_ptr message2_1;
		k_message_ptr message2_2;
/***********************************************************************/
/*CASE 1*/
/***********************************************************************/
/*CASE 2*/
/***********************************************************************/
/*CASE 3*/	assert(i == 2);		
		printf("TESTING SUCCESSFULL RECEIVE");
		message2_1 = k_receive_message();
		assert(message2_1 != NULL);
		assert(i == 2);
		printf("---->PASS\n");
/***********************************************************************/		
/*CASE 4*/	printf("TESTING SUCCESSFULL RELEASE");
		j = 0;		
		j = k_release_msg_env(message2_1);
		assert(i == 2);
		assert(j == ERROR_NONE);
		message2_1 = NULL;
		printf("---->PASS\n\n");
/***********************************************************************/
/*CASE 5*/	i = 3;
		printf("TESTING 2 FAILED REQUESTS:\n");
		
		message2_1 = k_request_msg_env();
		assert(message2_1 != NULL);
		printf("Env1-Taken");
		message2_2 = k_request_msg_env();
		assert(message2_2 != NULL);
		printf(", Env2-Taken\n");
		i = 4;
		k_release_processor();

		assert(i == 6);
		printf("-->Blocked\n");
		printf("TESTING 2 FAILED REQUESTS---->PASS\n\n");
/***********************************************************************/
/*CASE 6*/	printf("TESTING SINGLE RETURN TO READY STATE:\n");
		i = 7;
		j = 0;
		j = k_release_msg_env(message2_1);
		assert(j == ERROR_NONE);
		message2_1 = NULL;
		printf("Envelope Released");
		k_release_processor();
		
		assert(i == 8);
		printf("TESTING SINGLE RETURN TO READY STATE---->PASS\n\n");
/***********************************************************************/
/*CASE 7*/	printf("TESTING SECOND RETURN TO READY STATE:\n");
		i = 9;
		j = 0;
		j = k_release_msg_env(message2_2);
		assert(j == ERROR_NONE);
		message2_2 = NULL;
		printf("Envelope Released");
		k_release_processor();
/***********************************************************************/		
/*CASE 8*/	assert(i == 11);
		i = 12;
		printf("Process 2 Requests Envelope");
		message2_1 = k_request_msg_env();
		
		if(i == 14 || i == 15)
			printf("FAIL");

		assert(i == 17);
		assert(message2_1 != NULL);
		printf(" and Retrieved by Process 2\n");
		printf("TESTING REBLOCK ON REQUEST---->PASS\n\n");
/***********************************************************************/
/*CASE 9*/	printf("TESTING BLOCKED ON RECEIVE");
		i = 18;
		message2_2 = k_receive_message();
		
		if(i == 18 || i == 19 || i == 20)
			printf("FAIL");
/***********************************************************************/
/*CASE 10*/	assert(i == 23);		
		assert(message2_2 != NULL);
		printf("---->PASS\n");	



k_get_trace_buffers(message2_1);
	
/***********************************************************************/
/*CASE 11*/	j = 2;
		printf("TESTING FAILED SEND ON NONEXISTANT PID");
		j = k_send_message(5, message2_2);
		assert(j == ERROR_INVALID_PARAMETERS);
		printf("---->PASS\n");		
/***********************************************************************/
/*CASE 12*/	j = 2;
		printf("TESTING FAILED SEND ON NULL MESSAGE");
		j = k_send_message(1, NULL);
		assert(j == ERROR_INVALID_PARAMETERS);
		printf("---->PASS\n");		
/***********************************************************************/
/*CASE 13*/	j = 2;
		printf("TESTING FAILED RELEASE");		
		j = k_release_msg_env(NULL);
		assert(j == ERROR_INVALID_PARAMETERS);
		printf("---->PASS\n\n");		
/***********************************************************************/
/*IPROCESS*/	k_current_process->p_status = STATUS_READY;  
/*CASES   */	k_priority_queue_enqueue(k_current_process, k_readyPQ);
		k_context_switch(pcb2, pcb4);
		
		printf("---->FAIL\n");
/***********************************************************************/
		exit(0);
	}
}

void proc_3()
{
	while(1)
	{
		k_message_ptr message3;
/**********************************************************/
/*CASE 1*/
/**********************************************************/
/*CASE 2*/
/**********************************************************/
/*CASE 3*/
/**********************************************************/
/*CASE 4*/
/**********************************************************/
/*CASE 5*/	assert(i == 4);
		i = 5;
		printf("Process 3 Requesting Envelope");
		message3 = k_request_msg_env();
/**********************************************************/
/*CASE 6*/	assert(i == 7);
		i = 8;
		assert(message3 != NULL);
		printf(" and Retrieved by Process 3\n");
		k_release_processor();
/**********************************************************/
/*CASE 7*/	assert(i == 9);
		i = 10;
		k_release_processor();
/**********************************************************/
/*CASE 8*/	assert(i == 12);
		printf(" and is blocked\n");
		j = 0;
		j = k_release_msg_env(message3);
		assert(j == ERROR_NONE);
		message3 = NULL;
		printf("Process 3 Releases an Envelope");
		i = 13;
		message3 = k_request_msg_env();
		assert(i == 13);
		assert(message3 != NULL);
		printf(" and Retrieves it Again\n");
		i = 14;
		k_release_processor();

		assert(i == 15);
		printf("Process 2 is Still Blocked\n");
		j = 0;
		j = k_release_msg_env(message3);
		assert(j == ERROR_NONE);
		message3 = NULL;
		printf("Envelope Released");
		i = 16;
		k_release_processor();
/**********************************************************/
/*CASE 9*/	assert(i == 18);
		i = 19;
		k_release_processor();

		assert(i == 20);
		printf("---->PASS\n");
/**********************************************************/
/*CASE 10*/	printf("TESTING REACTIVATION FROM BLOCKED ON RECEIVE");
		i = 21;
		k_release_processor();

		assert(i == 22);
		i = 23;
		k_release_processor();
/**********************************************************/
		exit(0);	
	}
}

void proc_4()
{
	while(1)
	{
		k_message_ptr message4;
/***********************************************************************/
/*IPROCESS*/	printf("TESTING IPROCESS DOES NOT BLOCK ON REQUEST");
/*CASES   */	message4 = k_request_msg_env();
		assert(message4 == NULL);
		printf("---->PASS\n");
		
		printf("TESTING IPROCESS DOES NOT BLOCK ON RECEIVE");
		message4 = k_receive_message();
		assert(message4 == NULL);
		printf("---->PASS\n\n");
/***********************************************************************/

		

		exit(0);
	}
}

int main()
{
	printf("\nTESTING IPC FUNCTIONS:\n\n");
	int j;

	// Initialize structures;
	k_global_init();
	k_scheduler_init();
	k_ipc_init(2);	

	int pid[4];
	int priority[4];
	int is_iprocess[4];
	void *start_address[4];

	int num_proc = 4;
	
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

	pid[3] = 4;
	priority[3] = 0;
	is_iprocess[3] = 1;
	start_address[3] = (void *)&proc_4;
	
	k_itable_ptr init_table;
	init_table = k_itable_init(num_proc, pid, priority, is_iprocess, start_address);
	k_process_init(num_proc, init_table);
	
	pcb = k_pid_to_PCB_ptr(1);
	pcb2 = k_pid_to_PCB_ptr(2);
	pcb3 = k_pid_to_PCB_ptr(3);
	pcb4 = k_pid_to_PCB_ptr(4);
	
	i=1;
	k_process_switch();
}

