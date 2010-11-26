#ifndef K_INIT_H
#define K_INIT_H

#include "k_scheduler.h"
#include "k_ipc.h"
#include "k_utility.h"
#include "k_itable.c"
#include "api.h"
#include "k_interrupt_handler.h"
#include "k_init_struct.h"
#include "k_defines.h"
#include "k_globals.h"
#include "k_system_proc.h"
#include "k_i_proc.h"
#include "user_proc.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <signal.h>
#include <fcntl.h>
#include <setjmp.h>
#include <assert.h>

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
