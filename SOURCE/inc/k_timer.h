#ifndef K_TIMER_H
#define K_TIMER_H

#include "k_ipc.h"
#include "k_defines.h"

/****************************************************************
 Timer Functions
 ----------------------------------------------------------------
 This file contains all the timer functions that are provided via 
 the user api.
*****************************************************************/

/*************************
* Function Declarations
*************************/

int k_request_delay(int time_delay, int wakeup_code, MsgEnv *message_envelope);

#endif
