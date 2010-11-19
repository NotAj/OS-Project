#include <stdio.h>

int main()
{
	// TODO
	// STRUCTS
	io_buffer.c
	timeout_queue.c

	// Kernel
	scheduler.c // queue.c, priority_queue.c

	api.c		// all kernel

	// Processes	// api.c for all
	user_a.c		
	user_b.c
	user_C.c
	null.c
	wall_clock.c
	cci.c
	i_timer.c	
	i_crt.c
	i_kb.c			

	// Helpers
	kb_helper.c   	// io_buffer.c
	crt_help.c	// io_buffer.c	
}

// ADD K_PRIORITY_QUEUE_REMOVE or do some hacky shit in change_process_priority
