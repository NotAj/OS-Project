#include "user_proc.h"

void proc_A()
{
	int num;
	MsgEnv *msg = receive_message(); // Sent by CCI in response to s command
	MsgEnv *out_msg = request_msg_env();
	release_msg_env(msg);
	num = 0;
	while(1)
	{
		msg = request_msg_env();
		msg->msg_type = MSG_TYPE_COUNT_REPORT;
		msg->msg_text[1] = num;
		//sprintf(out_msg->msg_text, "Sending to Process B\n");
		//send_console_chars(out_msg);
		//while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
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
		do
		{
			msg = receive_message();
		}
		while (msg->msg_type != MSG_TYPE_COUNT_REPORT);
		// Will only forward messages of the correct type
		send_message(PID_USER_C,msg);
	}
}

void proc_C()
{
	MsgEnv_queue_ptr localMQ;
	localMQ = MsgEnv_queue_init();
	MsgEnv *msg;
	while(1)
	{
		if (k_message_queue_is_empty(localMQ))
		{
			msg = receive_message();
		}
		else
		{
			msg = MsgEnv_queue_dequeue(localMQ);
		}
	
		if (msg->msg_type == MSG_TYPE_COUNT_REPORT)
		{
			if ((msg->msg_text[1] % 20) == 0)
			{	
				printf("Printing\n");
				sprintf(msg->msg_text, "Process C->%d\n", msg->msg_text[1]);
				send_console_chars(msg);
				while (receive_message()->msg_type != MSG_TYPE_DISPLAY_ACK);
				printf("Printing2\n");
				request_delay(100, MSG_TYPE_WAKEUP_10, msg); // Request 10sec delay
				while (1)
				{
					printf("Printing3\n");
					msg = receive_message();
					if (msg->msg_type == MSG_TYPE_WAKEUP_10)
						break;
					else
						MsgEnv_queue_enqueue(msg, localMQ); 
				}
			}	
		}
		release_msg_env(msg);
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
		int delay = 10;
		sprintf(msg->msg_text, "Waiting for User Input:\n");
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
	while(1)
	{
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
