#ifndef K_GLOBALS_H
#define K_GLOBALS_H

#include <stdlib.h>
#include "k_pcb.h"
#include "k_message.h"
#include "k_queue.h"
#include "k_priority_queue.h"
#include "k_message_queue.h"
#include "k_tracebuffer.h"

/***************************************
 Global Variables
****************************************/
k_PCB_ptr k_current_process;		// Points to PCB of currently executing process
k_PCB_ptr k_interrupted_process;	// Points to PCB of interrupted process
int k_atomic_flag;					// Flag controlling calls to atomic
//#ifdef K_QUEUE_H
k_queue_ptr k_allQ;					// Queue contains all process in the RTX
k_priority_queue_ptr k_readyQ;		// PQ containing all ready process
k_priority_queue_ptr k_blockedQ;	// PQ containing all blocked_on_allocate processes
k_message_queue k_freeQ;			// Queue containing all free message envelopes
int k_clock_h;						// Wall Clock time in hours
int k_clock_m;						// Wall Clock time in minutes
int k_clock_s;						// Wall Clock time in seconds
int k_clock_tick;					// System time in clock ticks (100ms per tick)
int k_display_clock;				// Flag controlling display of wall clock
k_tracebuffer_ptr k_send_TB;		// Sent message TB array (16 last sends)
k_tracebuffer_ptr k_receive_TB;   // Receive message TB array (16 last receives)

#endif
