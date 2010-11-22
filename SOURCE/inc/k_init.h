#ifndef K_INIT_H
#define K_INIT_H

#include <stdlib.h>
#include "k_scheduler.h"
//#include "k_ipc.h"
#include "k_pcb.h"
#include "k_message.h"
#include "k_queue.h"
#include "k_priority_queue.h"
#include "k_message_queue.h"
#include "k_tracebuffer.h"
#include "k_itable.c"
#include "k_init_struct.h"
#include "k_defines.h"
#include "k_globals.h"
#include <signal.h>
#include <setjmp.h>

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
void k_scheduler_init();

void k_ipc_init(int msg_env_num);

void k_process_init();

void k_signal_init();

void k_init();

#endif
