#ifndef K_I_PROC_H
#define K_I_PROC_H

#include "api.h"
#include "k_timeout_queue.h"
#include <stdio.h>

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
