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

/****************************************************************
 I-Processes
 ----------------------------------------------------------------
 I proceses are a  solution to interrupt handling. They are triggered
 by the Interupt Handler

*****************************************************************/

/*************************
* Function Declarations
*************************/

void key_i_proc();

void crt_i_proc();

void timer_i_proc();

#endif
