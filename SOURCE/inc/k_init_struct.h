#ifndef K_INIT_STRUCT_H
#define K_INIT_STRUCT_H

#include <stdlib.h>
#include "k_pcb.h"
#include "k_message.h"
#include "k_queue.h"
#include "k_priority_queue.h"
#include "k_message_queue.h"
#include "k_tracebuffer.h"
#include "k_itable.c"

/****************************************************************
 Struct Initalizations
 ----------------------------------------------------------------
 This file contains code for all the struct initalizations. These
 functions are used during initalization, as well as during testing 
 of the OS.

*****************************************************************/

/*************************
* Type Declarations
*************************/

/*************************
* Function Declarations
*************************/
k_PCB_ptr k_PCB_init(int p_pid, int p_priority, int p_status, void *k_start_address);

k_message_ptr k_message_init();

k_queue_ptr k_queue_init();

k_priority_queue_ptr k_priority_queue_init();

k_message_queue_ptr k_message_queue_init();

k_tracebuffer_ptr k_tracebuffer_init();

#endif
