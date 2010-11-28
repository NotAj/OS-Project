#include "user_proc.h"

void proc_A()
{
	int num;
	MsgEnv *msg = receive_message(); // Sent by CCI in response to s command
	release_msg_env(msg);
	num = 0;
	while(1)
	{
		// Request message, fill data field and send to Process B
		msg = request_msg_env();
		msg->msg_type = MSG_TYPE_COUNT_REPORT;
		msg->msg_text[1] = num;
		send_message(PID_USER_B,msg);
		num++;
		release_processor();
	}
}

void proc_B()
{
	MsgEnv *msg;
	while(1)
	{
		// Process B receives a message then forwards it to C	
		msg = receive_message();
		send_message(PID_USER_C,msg);
	}
}

void proc_C()
{
	// Set up local queue
	MsgEnv_queue localMQ;
	(&localMQ)->head = (&localMQ)->tail = NULL;
	MsgEnv *msg;
	while(1)
	{
		// Receive message with priority given to local queue
		if (k_message_queue_is_empty(&localMQ))
		{
			msg = receive_message();
		}
		else
		{
			msg = MsgEnv_queue_dequeue(&localMQ);
		}
		// Only interested in count_report as other types handled inside loop	
		if (msg->msg_type == MSG_TYPE_COUNT_REPORT)
		{
			// If data divisible by 20, output "Process C" to screen
			if ((msg->msg_text[1] % 20) == 0)
			{	
				sprintf(msg->msg_text, "Process C\n");
				send_console_chars(msg);
				msg = receive_message();
				while (msg->msg_type != MSG_TYPE_DISPLAY_ACK)
				{
					// If msg not display_ack, send back to self, so we don't lose it
					send_message(PID_USER_C, msg);
					msg = receive_message();
				}
				request_delay(100, MSG_TYPE_WAKEUP_10, msg); // Request 10sec delay
				while (1)
				{
					// Check for wakeup_10 message
					msg = receive_message();
					if (msg->msg_type == MSG_TYPE_WAKEUP_10)
					{
						// Release message if finished with it
						release_msg_env(msg); 						
						break;
					}
					// Msg is not wakeup, enqueue to local queue so we don't lose it, but can still block waiting for delay
					else 					{
						MsgEnv_queue_enqueue(msg, &localMQ); 
					}
				}
			}
			else // If data field not divisible by 20, release message
			{
				release_msg_env(msg); 	
			}
		}
		release_processor();
	}
}

void proc_D()
{
	MsgEnv *msg = request_msg_env();
	MsgEnv *msg2 = request_msg_env();
	MsgEnv *msg3 = request_msg_env();	
	send_message(PID_USER_A, msg3);
	while(1)
	{
		int delay = 50;
	//	sprintf(msg->msg_text, "Waiting for User Input:\n");
		sprintf(msg->msg_text, "5 second timeout:\n");
		request_delay(delay,MSG_TYPE_WAKEUP_CODE,msg2);
		while (receive_message()->msg_type != MSG_TYPE_WAKEUP_CODE);
		send_console_chars(msg);
		while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
	
		get_console_chars(msg2);
		do
		{
			msg2 = receive_message();
		} while (msg2->msg_type != MSG_TYPE_CONSOLE_INPUT);
		send_console_chars(msg2);
		while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
		release_processor();
	}
/*		do
		{
			msg = receive_message();
		} while (msg->msg_type != MSG_TYPE_DISPLAY_ACK);
		//terminate();E
*/		/*	if (msg->msg_text[0] != '\0')
		{	
			send_console_chars(msg);
			while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
			msg->msg_text[0] = '\0';
			request_delay(10,10, msg);
			receive_message();
		}*/
	//		terminate();
	//	request_delay(10,1,msg);
//	}
}

void proc_E()
{	
	MsgEnv *msg = request_msg_env();
	MsgEnv *msg2 = request_msg_env();
	while(1)
	{
		int delay = 70;
	//	sprintf(msg->msg_text, "Waiting for User Input:\n");
		sprintf(msg->msg_text, "7 second timeout:\n");
	
		request_delay(delay,MSG_TYPE_WAKEUP_CODE,msg2);
		while (receive_message()->msg_type != MSG_TYPE_WAKEUP_CODE);
		send_console_chars(msg);
		while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
		release_processor();	
	}
}

void proc_F()
{
	while(1)
	{
		release_processor();
	}
}

