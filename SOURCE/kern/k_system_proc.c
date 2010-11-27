#include "k_system_proc.h"

void proc_null()
{
	while(1)
	{
		// Purpose of NULL process is to always be ready to run.
		// Process continuously gives up control, lets new free processes to run asap
		release_processor();
	}
}

void proc_wall_clock()
{

	return;
}
