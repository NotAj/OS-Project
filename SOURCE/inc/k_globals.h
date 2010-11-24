#ifndef K_GLOBALS_H
#define K_GLOBALS_H

#include <stdlib.h>
#include "k_pcb.h"
#include "k_message.h"
#include "k_queue.h"
#include "k_priority_queue.h"
#include "k_message_queue.h"
#include "k_timeout_queue.h"
#include "k_tracebuffer.h"
#include "k_io_buffer.c"

/***************************************
 Global Variables
****************************************/
k_PCB_ptr k_current_process;		// Points to PCB of currently executing process
k_PCB_ptr k_interrupted_process;	// Points to PCB of interrupted process
int k_atomic_flag;			// Flag controlling calls to atomic
k_queue_ptr k_allQ;			// Queue contains all process in the RTX
k_priority_queue_ptr k_readyPQ; 	// PQ containing all ready process
k_priority_queue_ptr k_blockedPQ; 	// PQ containing all blocked_on_allocate processes
k_message_queue_ptr k_freeMQ; 		// Queue containing all free message envelopes
k_timeout_queue_ptr k_TQ;		// Queue containing timeout requests
int k_clock_h;				// Wall Clock time in hours
int k_clock_m;				// Wall Clock time in minutes
int k_clock_s;				// Wall Clock time in seconds
int k_clock_tick;			// System time in clock ticks (100ms per tick)
int k_display_clock;			// Flag controlling display of wall clock
k_tracebuffer_ptr k_sendTB;		// Sent message TB array (16 last sends)
k_tracebuffer_ptr k_receiveTB;		// Receive message TB array (16 last receives)
k_io_buffer_ptr k_input_buf;		// Keyboard buffer
k_io_buffer_ptr k_output_buf;		// CRT buffer
int k_RTX_pid;					// PID of the RTX
int k_kbd_helper_pid;			// PID of the kdb helper, used to signal termination
int k_crt_helper_pid;			// PID of the crt helper, used to signal termination
int k_inputfile_fid;			// FID of the shared mem file, used in termination
int k_outputfile_fid;			// FID of the shared mem file, used in termination
char *k_inputfile_path;			// Path of the shared mem file
char *k_outputfile_path;		// Path of the shared mem file

#endif
