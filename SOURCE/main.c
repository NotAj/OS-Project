#include "k_init.h"
#include "k_scheduler.h"
#include "k_ipc.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	k_init();
	k_process_switch(); // At this point, process_switch to the first ready process, OS starts
} 
