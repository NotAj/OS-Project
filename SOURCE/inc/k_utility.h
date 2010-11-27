#ifndef K_UTILITY_H
#define K_UTILITY_H

#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include "k_pcb.h"
#include "k_queue.h"
#include "k_io_buffer.c"
#include "k_defines.h"

/****************************************************************
 Utility Functions
 ----------------------------------------------------------------
 This file contains all the utility functions that are needed for
 the user api, or for use in other functions 
*****************************************************************/

/*************************
* Function Declarations
*************************/
void k_terminate();

k_PCB_ptr k_pid_to_PCB_ptr (int pid);

int k_request_delay(int delay_time, int wakeup_code, MsgEnv *message_envelope);

#endif
