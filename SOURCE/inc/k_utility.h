#ifndef K_UTILITY_H
#define K_UTILITY_H

#include <stdlib.h>
#include "k_pcb.h"
#include "k_queue.h"
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
k_PCB_ptr k_pid_to_PCB_ptr (int pid);

#endif
