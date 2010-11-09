#include "pcb.h"

/****************************************************************
 PCB Data structure
 ----------------------------------------------------------------
 This structure contains all important information on each process
 in the RTX. A PCB for each process is created during intialization
 and is tracked on the various scheduling queues and the allQ. 
 Each PCB contains the PID, status, priority of a process. It also
 contains the stack pointer for each process, as well as a field to
 store the context when switching processes. Each process also has
 a queue of pending messages.

*****************************************************************/


