#include "k_itable.c"
#include "k_init_struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int count;
int i;

void proc_1()
{count == i * 10;}

void proc_2()
{count == i * 10;}

void proc_3()
{count == i * 10;}

void proc_4()
{count == i * 10;}

void proc_5()
{count == i * 10;}

int main()
{
	k_itable_ptr table;
	int pid[5];
	int status[5];
	int priority[5];
	void *start_address[5];  
	
	pid[0] = 1;
	status[0] = 1; 
	priority[0] = 1;
	start_address[0] = (void *) &proc_1;

	pid[1] = 2;
	status[1] = 2;
	priority[1] = 2;
	start_address[1] = (void *) &proc_2;
		
	pid[2] = 3;
	status[2] = 3;
	priority[2] = 3;
	start_address[2] = (void *) &proc_3;

	pid[3] = 4;
	status[3] = 4;
	priority[3] = 4;
	start_address[3] = (void *) &proc_4;

	pid[4] = 5;
	status[4] = 5;
	priority[4] = 5;
	start_address[4] = (void *) &proc_5;

	printf("Testing Itable Initialization");
		
	// Initialize itable by passing in array of fields
	table = k_itable_init(5,pid,status,priority,start_address);
	int i;
	for (i=0;i<5;i++)
	{
		// Verify fields initialized properly
		assert(table->pid[i] == pid[i]);
		assert(table->status[i] == status[i]);
		assert(table->priority[i] == priority[i]);
		assert(table->start_address[i] == start_address[i]);
		count = 10 * i;
		// Verify can lanch function from start_address in itable
		void (*fp)();
		fp = start_address[i];		
		fp();
	}
	printf("--->PASS\n");
	printf("ITABLE PASSED\n");
}
