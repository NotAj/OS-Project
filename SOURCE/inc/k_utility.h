#ifndef UTILITY_H
#define UTILITY_H

#include <stdlib.h>
#include "k_pcb.h"
#include "k_queue.h"
#include "defines.h"

/****************************************************************
 Utility Functions
 ----------------------------------------------------------------
 This file contains all the utility functions that are needed for
 the user api, or for use in other functions 
*****************************************************************/
/*************************
* Function Declarations
*************************/
k_PCB_ptr pid_to_PCB_ptr (int pid, k_queue_ptr Q);

#endif
