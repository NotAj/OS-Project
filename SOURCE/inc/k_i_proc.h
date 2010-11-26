#ifndef K_I_PROC_H
#define K_I_PROC_H

#include "k_pcb.h"
#include "k_queue.h"
#include "k_priority_queue.h"
#include "k_scheduler.h"
#include "k_message.h"
#include "k_message_queue.h"
#include "k_tracebuffer.h"
#include "api.h"
#include "k_globals.h"
#include "k_ipc.h"
#include "k_init_struct.h"
#include "k_defines.h"
#include "k_io_buffer.c"
#include "k_timeout_queue.h"

/****************************************************************
 I-Processes
 ----------------------------------------------------------------
 I proceses are a  solution to interrupt handling. They are triggered
 by the Interupt Handler

*****************************************************************/

/*************************
* Function Declarations
*************************/

void k_key_i_proc();

void k_crt_i_proc();

void k_timer_i_proc();

#endif
