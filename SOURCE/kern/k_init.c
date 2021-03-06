#include "k_init.h"


void k_global_init()
{
	extern k_PCB_ptr k_current_process;
	extern k_PCB_ptr k_interrupted_process;
	extern int k_atomic_count;		
	extern int k_clock_h;	
	extern int k_clock_m;		
	extern int k_clock_s;			
	extern long k_clock_tick;			
	extern int k_display_clock;			
	extern int k_kbd_helper_pid;
	extern int k_crt_helper_pid;
	extern int k_inputfile_fid;
	extern int k_outputfile_fid;
	extern char *k_inputfile_path;
	extern char *k_outputfile_path;

	k_current_process = NULL;
	k_interrupted_process = NULL;
	k_atomic_count = 1;
	k_clock_h = 0;
	k_clock_m = 0;
	k_clock_s = 0;
	k_clock_tick = 0;
	k_display_clock = 0;
	k_kbd_helper_pid = 0;
	k_crt_helper_pid = 0;
	k_inputfile_fid = 0;
	k_outputfile_fid = 0;
	// Name shared mem files
	// Only things known at the start, so do it here
	k_RTX_pid = getpid();
	k_inputfile_path = (char *) malloc(sizeof("helper/inputfile"));
	k_inputfile_path = "helpers/inputfile";
	k_outputfile_path = (char *) malloc(sizeof("helper/outputfile"));
	k_outputfile_path = "helpers/outputfile";
}

void k_helper_init()
{
	int result;
	caddr_t mmap_ptr;

	extern k_io_buffer_ptr k_input_buf; 
	extern k_io_buffer_ptr k_output_buf;
	extern int k_RTX_pid;
	extern int k_kbd_helper_pid;
	extern int k_crt_helper_pid;
	extern int k_inputfile_fid;
	extern int k_outputfile_fid;	
	extern char *k_inputfile_path;
	extern char *k_outputfile_path;
	
	//Create files
	k_inputfile_fid = open(k_inputfile_path, O_RDWR | O_CREAT , (mode_t) 0756);
	k_outputfile_fid = open(k_outputfile_path, O_RDWR | O_CREAT, (mode_t) 0756); 
	if ( k_outputfile_fid <= 0 || k_inputfile_fid <= 0)
	{
		k_terminate(ERROR_MMAP_INIT);  
	}
	//Change size of files to match buffer size
	ftruncate(k_outputfile_fid, BUFFER_SIZE); 			
	ftruncate(k_inputfile_fid, BUFFER_SIZE);

	// Arguments for execl function
	char rtx_pid[10],inputfile_fid[10], outputfile_fid[10];		
	sprintf(rtx_pid, "%d", k_RTX_pid);
	sprintf(inputfile_fid, "%d", k_inputfile_fid);
	sprintf(outputfile_fid, "%d", k_outputfile_fid);
	// Forking into Keyboard Helper
	k_kbd_helper_pid = fork();
	
	if(k_kbd_helper_pid == 0)				//Check that fork was successful
	{
		result = execl("./helpers/kbd_helper", "kbd_helper", rtx_pid, inputfile_fid, (char *)0);
		if (result < 0)
		{
			k_terminate(ERROR_HELPER_INIT); 
		}	
	}

	k_crt_helper_pid = fork();
	if(k_crt_helper_pid == 0)				//Check that fork was successful
	{
		result = execl("./helpers/crt_helper", "crt_helper", rtx_pid, outputfile_fid, (char *)0);
		if (result < 0)
		{
			k_terminate(ERROR_HELPER_INIT); 
		}
	}

	// Mapping memory to the file
	mmap_ptr = mmap((caddr_t) 0,	// Memory Location, 0 lets OS choose
			BUFFER_SIZE,			// How many bytes to mmap
			PROT_READ | PROT_WRITE, // Read and write permissions
			MAP_SHARED,    			// Accessible by another process
			k_inputfile_fid,      	// Which file is associated with mmap
			(off_t) 0);				// Offset in page frame
	if (mmap_ptr == MAP_FAILED)
	{
		k_terminate(ERROR_MMAP_INIT); 
	}
	
	k_input_buf = (k_io_buffer_ptr) mmap_ptr;	//Creating pointer to the sharedmem
	k_input_buf->wait_flag = 0;
	k_input_buf->length = 0;

	mmap_ptr = mmap((caddr_t) 0,	// Memory Location, 0 lets OS choose
			BUFFER_SIZE,			// How many bytes to mmap
			PROT_READ | PROT_WRITE, // Read and write permissions
			MAP_SHARED,    			// Accessible by another process
			k_outputfile_fid,      	// Which file is associated with mmap
			(off_t) 0);				// Offset in page frame
	if (mmap_ptr == MAP_FAILED)
	{
		k_terminate(ERROR_MMAP_INIT);
	}

	k_output_buf = (k_io_buffer_ptr) mmap_ptr;	//Creating pointer to the sharedmem
	k_output_buf->wait_flag = 1;
	k_output_buf->length = 0;
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
	extern MsgEnv *term_msg;
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
	
	// Initialize terminate msg
	term_msg = k_message_init();
}

void k_process_init(int num_process, k_itable_ptr init_table)
{	
	jmp_buf buf;
	extern k_priority_queue_ptr k_readyPQ;
	extern k_queue_ptr k_allQ;
	extern k_PCB_ptr k_current_process;
	extern int k_atomic_count;

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
			// Instruction moves the value (pcb->k_stack_pointer + STACK_SIZE - STACK_OFFSET) into register esp (holds stack pointer) with the constraint that a register must be used.
			// This sets the stack pointer inside the space allocated, and not just outside.
			char *sp_top = pcb->k_stack_pointer + STACK_SIZE - STACK_OFFSET;
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
				
				// Reset atomic count for the first time.
				k_current_process->k_atomic_count = 1; 
				if (k_current_process->p_status != STATUS_IPROCESS)
					k_atomic(0); // Enable interrupts if normal process
				
				void (*fp)() = k_current_process->k_start_address;
				fp(); // This will start execution from start_address()
				
				// NOTE that a process can never return here so this init approach requires that all processes never end (ie. House all processes in an infinite loop)
				k_terminate(ERROR_CONTEXT_SWITCH);
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
	extern k_io_buffer_ptr k_output_buf;
	// Set up signal handling

	sigset(SIGQUIT, die);
	sigset(SIGBUS, die); 	// Catch bus errors
	sigset(SIGHUP, die);
	sigset(SIGILL, die); 	// Illegal instruction
	sigset(SIGABRT, die);
	sigset(SIGTERM, die);
	sigset(SIGSEGV, die); 	// Catch segmentation faults
	sigset(SIGINT, die);	// Set ctrl + c to terminate O

	//Runs the interrupt handler whenever the signal is fired
	sigset (SIGALRM, k_interrupt_handler); // Linux clock signal
	sigset (SIGUSR1, k_interrupt_handler); // Keyboard helper signal
	sigset (SIGUSR2, k_interrupt_handler); // Crt helper signal

	ualarm(100000, 100000);	// Sets a SIGALRM to be fired every 100 ms
}

/*****************************************************************
 Really bad fix for the timing issue seen on startup. Issue is that 
 the helper processes are forked before signal handling is set up. Since
 the CRT helper process keeps firing a USR2 signal every 100msec, sometimes
 the startup isn't fast enough to get to signal setup before the signal fires.
 Since the signal is unhandled, it kills the RTX process. Tried moving helper
 initialization after signal handling, but that leads to OS initializing 
 sometimes before the helpers fork, leading to invalid states. 
 Here just specify a handler that does nothing, so the USR2 signal is handled
 and doesn't cause a terminate, then signal handling is set up normally. This
 is fine since we don't care about output this early on.
 Better fix would be to use the temp process used in process_init and have that
 enable atomicity to mask the USR2 signal.
 
 Technically this issue is a product of simulating IO on linux, so it's not 
 that big a deal right?
******************************************************************/
void fix()
{}

void k_init()
{
	int pid[PROCESS_NUM];
	int priority[PROCESS_NUM];
	int is_iprocess[PROCESS_NUM];
	void *start_address[PROCESS_NUM];
	extern k_PCB_ptr k_current_process;
	k_message_ptr startup_out;	

/*	setjmp(temp_pcb->k_jmp_buf);
	k_current_process = temp_pcb;	
	k_current_process->k_atomic_count = 0;
	k_atomic(1); // Just mask signals, don't care about this count after
*/
	sigset (SIGUSR2, fix); // Fix for startup timing issue. Correct handler will be set up later 

	k_itable_ptr init_table;	

	k_global_init(); // Set initial value of globals

	k_helper_init(); 
	
	k_ipc_init(MSG_ENV_NUM); // Initialize free message queue
	
	k_scheduler_init(); // Initialize scheduling queues

	// Set up fields of ITABLE	
	pid[0] = PID_NULL;
	priority[0] = PRIORITY_NUM - 1; // Set to lowest priority
	is_iprocess[0] = 0; 
	start_address[0] = &(proc_null);
	
	pid[1] = PID_USER_A;
	priority[1] = 2;
	is_iprocess[1] = 0; 
	start_address[1] = &(proc_A);

	pid[2] = PID_USER_B;
	priority[2] = 2; 
	is_iprocess[2] = 0; 
	start_address[2] = &(proc_B);

	pid[3] = PID_USER_C;
	priority[3] = 2; 
	is_iprocess[3] = 0; 
	start_address[3] = &(proc_C);
	
	pid[4] = PID_WALL_CLOCK;
	priority[4] = 0;
	is_iprocess[4] = 0;
	start_address[4] = &(proc_wall_clock);

	pid[5] = PID_CCI;
	priority[5] = 0;
	is_iprocess[5] = 0;
	start_address[5] = &(proc_CCI);

	pid[6] = PID_I_CRT;
	priority[6] = 0; 
	is_iprocess[6] = 1; 
	start_address[6] = &(k_crt_i_proc);

	pid[7] = PID_I_KB;
	priority[7] = 0; 
	is_iprocess[7] = 1; 
	start_address[7] = &(k_key_i_proc);
	
	pid[8] = PID_I_TIMER;
	priority[8] = 0;
	is_iprocess[8] = 1;
	start_address[8] = &(k_timer_i_proc);

// User processes used during testing.
/*	pid[9] = PID_USER_D;
	priority[9] = 0;
	is_iprocess[9] = 0;
	start_address[9] = &(proc_D);

	pid[10] = PID_USER_E;
	priority[10] = 0;
	is_iprocess[10] = 0;
	start_address[10] = &(proc_E);

	pid[11] = PID_USER_F;
	priority[11] = 3;
	is_iprocess[11] = 1;
	start_address[11] = &(proc_F);
*/
	init_table =k_itable_init(PROCESS_NUM, pid, priority, is_iprocess, start_address);
	k_process_init(PROCESS_NUM, init_table); // Initialize all processes using itable 

	// NOTE: Normally cannot longjmp if the function that setjmp was called in has returned, but since we've set up a different stack for each process, this is not a problem.
	k_signal_init(); // Set up signals
	// Print startup message, set system text color to red
	startup_out = k_message_init();	
	sprintf(startup_out->msg_text,"\033[2J\033[1;31m\033[H%s\033[1;33m%s\033[1;31m%s\033[1;33m%s\033[1;31m\n", "Initializing....\n\nWelcome to b", "O", "ri","S");
	send_console_chars(startup_out);
	// Don't wait for output confirmation
	//while(receive_message()->msg_type!=MSG_TYPE_DISPLAY_ACK);
} 

