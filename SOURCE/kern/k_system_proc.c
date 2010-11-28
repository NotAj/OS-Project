#include <stdlib.h>
#include <stdio.h>
#include "k_system_proc.h"
#include "api.h"

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
	while(1)
	{
		request_delay(10, MSG_TYPE_WALLCLOCK_DELAY, delay_msg);	//Request 1 second delay
		// Block process till wakeup message received
		while(receive_message()->msg_type != MSG_TYPE_WALLCLOCK_DELAY);	
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
			// Constantly output clock to row 0, column 72
			output_msg->msg_size = sprintf(output_msg->msg_text, "\033[s\033[H\033[K\033[0;72H\033[1;31m%02d\033[1;33m:\033[1;31m%02d\033[1;33m:\033[1;31m%02d\033[u", k_clock_h, k_clock_m, k_clock_s); 
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
		strcpy(crt_out->msg_text, "\033[1;33mCCI: \033[1;31m");		//prompt user for input
		if (send_console_chars(crt_out)==ERROR_NONE)	
			while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
		if (get_console_chars(key_in)==ERROR_NONE)		//get ready to receive  input
			while (receive_message()->msg_type != MSG_TYPE_CONSOLE_INPUT);
		
		//select variables to parse your strin command into		
		char command[2];
		char param1[8];		
		char param2[3];
		char param3[1];
		int cmd_no;

		cmd_no = sscanf(key_in->msg_text,"%2s %8s %3s %1s", command, param1, param2, param3);
		if (key_in->msg_type == MSG_TYPE_CONSOLE_INPUT)	//check whether the received envelope is an input and could succesfully get command
		{				 			
			if ((strncmp(command,"s",2)==0 || strncmp(command,"S",2)==0) && cmd_no == 1) 
			{
				MsgEnv *proc_a;	//create and send an empty envelope 
				proc_a = request_msg_env(); 	//to user process A
				send_message(PID_USER_A, proc_a);
				strcpy(crt_out->msg_text, "MESSAGE SENT TO USER PROCESS A\n");
				if (send_console_chars(crt_out)==ERROR_NONE);
					while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
			}
			
			else if ((strncmp(command,"ps",2)==0 || strncmp(command,"PS",2)==0 || strncmp(command,"Ps",2)==0 || strncmp(command,"pS",2)==0) && cmd_no == 1) 
			{
				request_process_status(crt_out);
				if (send_console_chars(crt_out)==ERROR_NONE)
					while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
			
			}

			else if ((strncmp(command,"cd",2)==0 || strncmp(command,"CD",2)==0 || strncmp(command,"Cd",2)==0 || strncmp(command,"cD",2)==0)&& cmd_no == 1) 	
			{
				if (k_display_clock == 0)
				{	
					strcpy(crt_out->msg_text, "DISPLAYING WALL CLOCK... \n");
					if (send_console_chars(crt_out)==ERROR_NONE);
						while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);			
					k_display_clock = 1;
				}
				else 
				{
					strcpy(crt_out->msg_text, "ALREADY DISPLAYING WALL CLOCK... \n");
					if (send_console_chars(crt_out)==ERROR_NONE);
							while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
				}
			}
			
			else if ((strncmp(command,"ct",2)==0 || strncmp(command,"CT",2)==0 || strncmp(command,"Ct",2)==0 || strncmp(command,"cT",2)==0) && cmd_no == 1) 	
			{
				if (k_display_clock == 1)
				{
					// Clear wallclock, then print
					strcpy(crt_out->msg_text, "\033[s\033[H\033[K\033[uHIDING WALL CLOCK... \n");
					if (send_console_chars(crt_out)==ERROR_NONE);
						while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);	
					k_display_clock = 0;
				}
				else 
				{
					strcpy(crt_out->msg_text, "WALL CLOCK ALREADY HIDDEN.... \n");
					if (send_console_chars(crt_out)==ERROR_NONE);
							while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
				}
			}
	
			else if ((strncmp(command,"c",2)==0 || strncmp(command,"C",2)==0) && cmd_no == 2) 
			{
				int hh, mm, ss;
				char a, b;
				if (sscanf(key_in->msg_text, "%*s %d %c %d %c %d", &hh, &a, &mm, &b, &ss) == 5)				
				{		
					if (hh<24 && mm<60 && ss<60 && hh>=0 && mm>=0 && ss>=0 && a==58 && b==58)
 					{
						k_clock_h = hh;
						k_clock_m = mm;
						k_clock_s = ss;
						strcpy(crt_out->msg_text, "WALL CLOCK SET\n");
						if (send_console_chars(crt_out)==ERROR_NONE);
							while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
					}
					else
					{
						strcpy(crt_out->msg_text, "INVALID INPUT \n");
						if (send_console_chars(crt_out)==ERROR_NONE);
							while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
					}
				}
				else
				{
					strcpy(crt_out->msg_text, "INVALID INPUT \n");
					if (send_console_chars(crt_out)==ERROR_NONE)
						while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
				}	
			}

			else if ((strncmp(command,"b",2)==0 || strncmp(command,"B",2)==0) && cmd_no == 1) 		
			{
				if (get_trace_buffers(crt_out) == ERROR_NONE)
				{
					if (send_console_chars(crt_out)==ERROR_NONE)
						while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
				}	
			}
	
			else if ((strncmp(command,"t",2)==0 || strncmp(command,"T",2)==0) && cmd_no == 1) 	
			{
				terminate();		
			}

			else if ((strncmp(command,"n",2)==0 || strncmp(command,"N",2)==0) && cmd_no == 3) 	
			{	
				int new_priority, process_id;
				if (sscanf(key_in->msg_text, "%*s %d %d", &new_priority, &process_id) == 2)				
				{				
					if (new_priority>=0 && new_priority<=3 && process_id >0 && process_id<=11)
 					{
						if (change_priority (new_priority, process_id) == ERROR_NONE)
						{		

							strcpy(crt_out->msg_text, "PRIORITY CHANGED \n");
							if (send_console_chars(crt_out)==ERROR_NONE)
								while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
						}
						else
						{
							strcpy(crt_out->msg_text, "INVALID INPUT \n");
							if (send_console_chars(crt_out)==ERROR_NONE)
								while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
						}
					}
					else
					{
						strcpy(crt_out->msg_text, "INVALID INPUT \n");
						if (send_console_chars(crt_out)==ERROR_NONE)
							while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
					}
				}
				else
				{
					strcpy(crt_out->msg_text, "INVALID INPUT \n");
					if (send_console_chars(crt_out)==ERROR_NONE)
						while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
				}			
			}

			else
			{
				strcpy(crt_out->msg_text, "INVALID INPUT \n");
				if (send_console_chars(crt_out)==ERROR_NONE)
					while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
			}	
		}
		release_processor();
	}	
}
