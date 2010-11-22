#ifndef K_GLOBALS_H
#define K_GLOBALS_H

#include <stdlib.h>
#include "k_pcb.h"
#include "k_message.h"
#include "k_queue.h"
#include "k_priority_queue.h"
#include "k_message_queue.h"
#include "k_tracebuffer.h"
#include "k_itable.c"
#include "k_init_struct.h"

/***************************************
 Global Variables
****************************************/
k_PCB_ptr k_current_process= NULL;	// Points to PCB of currently executing process
k_PCB_ptr k_interrupted_process = NULL;	// Points to PCB of interrupted process
int k_atomic_flag = 0;				// Flag controlling calls to atomic
k_queue_ptr k_allQ;					// Queue contains all process in the RTX
k_priority_queue_ptr k_readyPQ; 		// PQ containing all ready process
k_priority_queue_ptr k_blockedPQ; 	// PQ containing all blocked_on_allocate processes
k_message_queue_ptr k_freeMQ; 		// Queue containing all free message envelopes
int k_clock_h = 0;					// Wall Clock time in hours
int k_clock_m = 0;					// Wall Clock time in minutes
int k_clock_s = 0;					// Wall Clock time in seconds
int k_clock_tick = 0;				// System time in clock ticks (100ms per tick)
int k_display_clock = 0;			// Flag controlling display of wall clock
k_tracebuffer_ptr k_sendTB;			// Sent message TB array (16 last sends)
k_tracebuffer_ptr k_receiveTB;		// Receive message TB array (16 last receives)
k_itable_ptr itable;				// Itable used to initialize all processes

#endif
