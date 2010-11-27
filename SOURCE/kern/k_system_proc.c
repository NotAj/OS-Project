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

	//Allocate messages to be reused for requesting delay and outputting to crt
	MsgEnv *delay_msg = k_request_msg_env(); 
	MsgEnv *output_msg = k_request_msg_env();	
	int i;
	
	while(1)						//Loop forever
	{
		request_delay(10, MSG_TYPE_WAKEUP_CODE, delay_msg);	//Request 1 second delay
		//Block process till wakeup message received
		delay_msg = k_receive_message();	
		
		//If wakeup message received, update clock
		if(delay_msg->msg_type == MSG_TYPE_WAKEUP_CODE) 
		{
			(k_clock_s++ % 60);
			if(k_clock_s == 0)		//Seconds rolled over. Increment minute
			{
				(k_clock_m++ % 60);
				if (k_clock_m == 0)	//Minutes rolled over. Increment hour
					//No action taken on hours rolling over
					//Time will already read 00:00:00
					(k_clock_h++ % 24); 				
			}
			if(k_display_clock == 1) 	//If display flag set, send time to crt
			{
				i = sprintf(output_msg->msg_text, "%d:%d:%d", k_clock_h, k_clock_m, k_clock_s); 
				output_msg->msg_size = i;
				send_console_chars(output_msg);
			}
		}
		//If display_ack message received, assign pointer to output_msg so we don't lose allocated envelope
		else if(delay_msg->msg_type == MSG_TYPE_DISPLAY_ACK)	
		{	
			output_msg = delay_msg;
		}
		//If neither, we don't care.  Do nothing
	}
}
