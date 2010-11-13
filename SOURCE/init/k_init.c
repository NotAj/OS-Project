#include "k_init.h"

void k_global_init()
{
	extern k_PCB_ptr k_current_process;
	extern k_PCB_ptr k_interrupted_process;
	extern int k_atomic_flag;		
	extern int k_clock_h;	
	extern int k_clock_m;		
	extern int k_clock_s;			
	extern int k_clock_tick;			
	extern int k_display_clock;			

	k_current_process = NULL;
	k_interrupted_process = NULL;
	k_atomic_flag = 0;
	k_clock_h = 0;
	k_clock_m = 0;
	k_clock_s = 0;
	k_clock_tick = 0;
	k_display_clock = 0;
}

void k_helper_init()
{
	//TODO
}

void k_scheduler_init()
{
	extern k_queue_ptr k_allQ;
	extern k_priority_queue_ptr k_readyPQ;
	extern k_priority_queue_ptr k_blockedPQ;
	// Initialize all 3 scheduling queues
	k_allQ = k_queue_init();
	k_readyPQ = k_priority_queue_init();
	k_blockedPQ = k_priority_queue_init();
}

void k_ipc_init(int msg_env_num)
{
	extern k_message_queue_ptr k_freeMQ;
	extern k_tracebuffer_ptr k_sendTB;
	extern k_tracebuffer_ptr k_receiveTB;
	int i;
	k_message_ptr msg;
	// Initialize free message envelope queue
	k_freeMQ = k_message_queue_init();
	for (i=0; i < msg_env_num; i++)
	{
		// Initialize space for message envelopes, add to freeQ	
		msg = k_message_init();
		k_message_queue_enqueue(msg, k_freeMQ);
	}
	// Initialize tracebuffers
	k_sendTB = k_tracebuffer_init();
	k_receiveTB = k_tracebuffer_init();	
}

void k_process_init(int num_process, k_itable_ptr init_table)
{	
	jmp_buf buf;
	extern k_priority_queue_ptr k_readyPQ;
	extern k_queue_ptr k_allQ;
	extern k_PCB_ptr k_current_process;

	k_PCB_ptr pcb;
	int i;
	
	for(i=0; i<num_process; i++)
	{
		if(init_table->is_iprocess[i])
		{
			// Note parameters of k_PCB_init are (pid, status, priority, start_address)
			// Process is iprocess
			pcb = k_PCB_init(init_table->pid[i], STATUS_IPROCESS, init_table->priority[i], init_table->start_address[i]);
		}
		else
		{
			// Normal process
			pcb = k_PCB_init(init_table->pid[i], STATUS_READY, init_table->priority[i],  init_table->start_address[i]);
			k_priority_queue_enqueue(pcb, k_readyPQ);
		}
		pcb->k_stack_pointer = malloc(STACK_SIZE);
		k_queue_enqueue(pcb, 1, k_allQ);
		// Now initialize the starting context for each process
		if(!(setjmp(buf)))
		{
			// Set up stack pointer for this process
			// Note the stack offsets negatively so give it address at end of stack
			// Instruction moves the value (pcb->k_stack_pointer + STACK_SIZE) into register esp (holds stack pointer) with the constraint that a register must be used.
			char *sp_top = pcb->k_stack_pointer + STACK_SIZE;
			__asm__("movl %0, %%esp" : : "g" (sp_top));
			// NOTE output operand can't be an expression, so evaluate before asm.
			if(!(setjmp(pcb->k_jmp_buf))) // Context has just been saved, jump back 
			{
				longjmp(buf,1);
			}
			else // Here when restored context for the first time
			{
				// Create a function pointer containing start addr of the current pcb
				// Note that the pointer to pcb has been overwritten by the loop. 
				// Will be here if switched from the scheduler, so current_process global holds the process we're intested in.
				void (*fp)() = k_current_process->k_start_address;
				//atomic(off); //TODO// Enable interrupts for the first time
				fp(); // This will start execution from start_address()
				//TODO assert(0); 
				// NOTE that a process can never return here so this init approach requires that all processes never end (ie. House all processes in an infinite loop)
				//k_terminate();
			}
		}		
	}
	// Done setting up PCBs. OS will start by calling process switch. Process switch uses the current_process field to determine the process being switched from.
	pcb = k_PCB_init(-1,-1,-1, NULL); // Create throwaway pcb
	setjmp(pcb->k_jmp_buf); // Set the context of this pcb. Just need any valid point, since cannot pass in NULL, but will never jump back to this process.
	k_current_process = pcb; // Set the current_process field, will be overwritten by process_switch
	// At this point, ready to call process_switch to start OS
}

void k_signal_init()
{
	//TODO
	// Set up signal handling
	//sigset (SIGINT, terminate());	// Set ctrl + c to terminate OS
	//Runs the interrupt handler whenever the signal is fired
	//sigset (SIGALRM, interrupt_handler(14)); // Linux clock signal
	//sigset (SIGUSR1, interrupt_handler(30)); // Keyboard helper signal
	//sigset (SIGUSR2, interrupt_handler(31)); // Crt helper signal
	//ualarm(100000, 100000);	// Sets a SIGALRM to be fired every 100 ms
}

void k_init()
{
	int pid[PROCESS_NUM];
	int priority[PROCESS_NUM];
	int is_iprocess[PROCESS_NUM];
	void *start_address[PROCESS_NUM];

	k_itable_ptr init_table;	

	k_global_init(); // Set initial value of globals

	k_helper_init(); //TODO
	
	k_ipc_init(MSG_ENV_NUM); // Initialize free message queue
	
	k_scheduler_init(); // Initialize scheduling queues
	
	//TODO PROCESS ITABLE SETTING HERE	

	init_table = k_itable_init(PROCESS_NUM, pid, priority, is_iprocess, start_address);	
	k_process_init(PROCESS_NUM, init_table); // Initialize all processes using itable
	// NOTE: Normally cannot longjmp if the function that setjmp was called in has returned, but since we've set up a different stack for each process, this is not a problem.

	k_signal_init(); // Set up signals
	
	k_process_switch(); // At this point, process_switch to the first ready process, OS starts
} 
