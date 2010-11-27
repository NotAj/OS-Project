#include <stdlib.h>
#include <stdio.h>
#include "k_system_proc.h"
#include "api.h"
#include "k_defines.h"
#include "k_globals.h"
//#include <string.h>

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
			output_msg->msg_size = sprintf(output_msg->msg_text, "%02d:%02d:%02d", k_clock_h, k_clock_m, k_clock_s); 
			send_console_chars(output_msg);
			while(receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
		}
		release_processor();
	}
}

void proc_CCI()
{
	MsgEnv *key_in; 			//assign input/output envelope and allocate space
	key_in = request_msg_env();

	MsgEnv *crt_out;
	crt_out = request_msg_env();

	while (1)	//loop forever
	{
		crt_out->msg_text = "CCI:";		//prompt user for input
		if (send_console_chars(crt_out)==ERROR_NONE)	
			crt_out = receive_message();
printf("1");
		if (get_console_chars(key_in)==ERROR_NONE)		//get ready to receive  input
			key_in = receive_message();		//get queued msg
printf("2");		
		char command[5];

		if (key_in->msg_type == MSG_TYPE_CONSOLE_INPUT && sscanf(key_in->msg_text,"%s", command) == 1)	//check whether the received envelope is an input and could succesfully get command
		{	printf("%s", command);			 			
			if (strncmp(command,"s",1)==0) 
			{
				MsgEnv *proc_a;	//create and send an empty envelope 
				proc_a = request_msg_env(); 	//to user process A
				send_message(PID_USER_A, proc_a);
				printf("4");
			}
			
			else if (strncmp(command,"ps",2)==0) 
			{
printf("5");				request_process_status(crt_out);
				if (send_console_chars(crt_out)==ERROR_NONE)
					crt_out = receive_message();
			}

			else if (strncmp(command,"c",1)==0) 
			{
				int hh, mm, ss;
				if (sscanf(key_in->msg_text, "%*s %d %*c %d %*c %d", &hh, &mm, &ss) == 3)				
				{				
					if (hh<24 && mm<60 && ss<60 && hh>=0 && mm>=0 && ss>=0)
 					{
						k_clock_h = hh;
						k_clock_m = mm;
						k_clock_s = ss;
					}
					else
					{
						sscanf("INVALID_INPUT" ,"%s", crt_out->msg_text);
						if (send_console_chars(crt_out)==ERROR_NONE);
							crt_out = receive_message();
					}
				}
				else
				{
					sscanf("INVALID_INPUT" ,"%s", crt_out->msg_text);
					if (send_console_chars(crt_out)==ERROR_NONE)
						crt_out = receive_message();
				}	
			}

			else if (strncmp(command,"cd",2)==0) 	
			{
				k_display_clock = 1;
			}
			
			else if (strncmp(command,"ct",2)==0) 	
			{
				k_display_clock = 0;
			}
	
			else if (strncmp(command,"b",1)==0) 		
			{
				get_trace_buffers(crt_out);
				if (send_console_chars(crt_out)==ERROR_NONE)
					crt_out  = receive_message();	
			}
	
			else if (strncmp(command,"t",1)==0) 	
			{
				terminate();		
			}

			else if (strncmp(command,"n",1)==0) 	
			{	
				int new_priority, process_id;
				if (sscanf(key_in->msg_text, "%*s %d %d", &new_priority, &process_id) == 2)				
				{				
					if (new_priority>=0)
 					{
						change_priority (new_priority, process_id);				
					}
					else
					{
						sscanf("INVALID_INPUT" ,"%s", crt_out->msg_text);
						if (send_console_chars(crt_out)==ERROR_NONE)
							crt_out  = receive_message();
					}
				}
				else
				{
					sscanf("INVALID_INPUT" ,"%s", crt_out->msg_text);
					if (send_console_chars(crt_out)==ERROR_NONE)
						crt_out  = receive_message();
				}			
			}

			else
			{
				sscanf("INVALID_INPUT" ,"%s", crt_out->msg_text);
				if (send_console_chars(crt_out)==ERROR_NONE)
					crt_out  = receive_message();
			}	
		}
		release_processor();
	}	
}
