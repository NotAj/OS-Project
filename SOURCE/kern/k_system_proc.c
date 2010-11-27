#include <stdlib.h>
#include <stdio.h>
#include "k_system_proc.h"
#include "api.h"
#include "k_defines.h"
#include "k_globals.h"


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

	extern int k_clock_h;
	extern int k_clock_m;
	extern int k_clock_s;
	extern int k_display_clock;

	// Allocate messages to be reused for requesting delay and outputting to crt
	MsgEnv *delay_msg = k_request_msg_env(); 
	MsgEnv *output_msg = k_request_msg_env();	
	k_display_clock = 1;	
	while(1)
	{
		request_delay(10, MSG_TYPE_WAKEUP_CODE, delay_msg);	//Request 1 second delay
		// Block process till wakeup message received
		while(receive_message()->msg_type != MSG_TYPE_WAKEUP_CODE);	
		// Update clock
		k_clock_s = (k_clock_s + 1) % 60;
		if(k_clock_s == 0) // Seconds rolled over. Increment minute
		{
			k_clock_m = (k_clock_m + 1) % 60;
			if (k_clock_m == 0)	// Minutes rolled over. Increment hour
				// No action taken on hours rolling over
				// Time will already read 00:00:00
				k_clock_h = (k_clock_h + 1) % 24;
		}
		if(k_display_clock == 1) // If display flag set, send time to crt
		{
			output_msg->msg_size = sprintf(output_msg->msg_text, "%02d:%02d:%02d\n", k_clock_h, k_clock_m, k_clock_s); 
			send_console_chars(output_msg);
			while(receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
		}
		release_processor();
	}
}
