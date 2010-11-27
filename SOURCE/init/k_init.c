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
	extern int k_kbd_helper_pid;
	extern int k_crt_helper_pid;
	extern int k_inputfile_fid;
	extern int k_outputfile_fid;
	extern char *k_inputfile_path;
	extern char *k_outputfile_path;

	k_current_process = NULL;
	k_interrupted_process = NULL;
	k_atomic_flag = 0;
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
		//k_terminate() //TODO 
		assert(k_outputfile_fid > 0);
		assert(k_inputfile_fid > 0);
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
			//k_terminate() //TODO
			assert(result >= 0);
		}	
	}

	k_crt_helper_pid = fork();
	if(k_crt_helper_pid == 0)				//Check that fork was successful
	{
		result = execl("./helpers/crt_helper", "crt_helper", rtx_pid, outputfile_fid, (char *)0);
		if (result < 0)
		{
			//k_terminate() //TODO
			assert(result >= 0);
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
		//k_terminate(); //TODO
		assert(mmap_ptr != MAP_FAILED);
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
		//k_terminate(); //TODO
		assert(mmap_ptr != MAP_FAILED);
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
	// Set up signal handling

	sigset(SIGINT, die); 	// Catch kill signals
	sigset(SIGBUS, die); 	// Catch bus errors
	sigset(SIGHUP, die);
	sigset(SIGILL, die); 	// Illegal instruction
	sigset(SIGQUIT, die);
	sigset(SIGABRT, die);
	sigset(SIGTERM, die);
	sigset(SIGSEGV, die); 	// Catch segmentation faults
	sigset(SIGINT, die);	// Set ctrl + c to terminate OS

	//Runs the interrupt handler whenever the signal is fired
	sigset (SIGALRM, k_interrupt_handler); // Linux clock signal
	sigset (SIGUSR1, k_interrupt_handler); // Keyboard helper signal
	sigset (SIGUSR2, k_interrupt_handler); // Crt helper signal

	ualarm(100000, 100000);	// Sets a SIGALRM to be fired every 100 ms
}

void k_init()
{
	int pid[PROCESS_NUM];
	int priority[PROCESS_NUM];
	int is_iprocess[PROCESS_NUM];
	void *start_address[PROCESS_NUM];

	k_itable_ptr init_table;	

	k_global_init(); // Set initial value of globals

	k_helper_init(); 
	
	k_ipc_init(MSG_ENV_NUM); // Initialize free message queue
	
	k_scheduler_init(); // Initialize scheduling queues
	
	//TODO PROCESS ITABLE SETTING HERE	
	pid[0] = PID_NULL;
	priority[0] = PRIORITY_NUM - 1; // Set to lowest priority
	is_iprocess[0] = 0; 
	start_address[0] = &(proc_null);
	
	pid[1] = PID_USER_A;
	priority[1] = PRIORITY_NUM - 1; // Set to lowest priority
	is_iprocess[1] = 0; 
	start_address[1] = &(proc_A);

	pid[2] = PID_USER_B;
	priority[2] = PRIORITY_NUM - 1; // Set to lowest priority
	is_iprocess[2] = 0; 
	start_address[2] = &(proc_B);

	pid[3] = PID_USER_C;
	priority[3] = PRIORITY_NUM - 1; // Set to lowest priority
	is_iprocess[3] = 0; 
	start_address[3] = &(proc_C);
	
	pid[4] = PID_USER_D;
	priority[4] = 0;
	is_iprocess[4] = 0;
	start_address[4] = &(proc_D);

	pid[5] = PID_I_CRT;
	priority[5] = 0; 
	is_iprocess[5] = 1; 
	start_address[5] = &(k_crt_i_proc);

	pid[6] = PID_I_KB;
	priority[6] = 0; // Set to lowest priority
	is_iprocess[6] = 1; 
	start_address[6] = &(k_key_i_proc);
	
	pid[7] = PID_I_TIMER;
	priority[7] = 0;
	is_iprocess[7] = 1;
	start_address[7] = &(k_timer_i_proc);

	init_table = k_itable_init(8, pid, priority, is_iprocess, start_address);	//TODO
	k_process_init(8, init_table); // Initialize all processes using itable //TODO

	// NOTE: Normally cannot longjmp if the function that setjmp was called in has returned, but since we've set up a different stack for each process, this is not a problem.

	k_signal_init(); // Set up signals	
} 
