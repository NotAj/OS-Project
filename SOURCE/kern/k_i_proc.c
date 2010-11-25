#include "k_i_proc.h" 
#include "k_messages.h"
#include "k_pcb.h"


void key_i_proc()
{
	k_PCB_ptr prev_process;
	k_message_ptr input_msg;
	extern k_queue_ptr k_allQ;
	extern k_PCB_ptr k_current_process;

	while (1) //loop forever
	{
		//save interrupted process
		prev_process = k_current_process;
		
		//set iprocess as current process
		k_current_process = pid_to_PCB_ptr(PID_I_KB);
		
		//Only forward the kb input if there is a process that wants kb input (signified 			by a msg in the received message queue
		if (k_current_process->p_received_MsgEnvQ->head != NULL)
		
		//receive message envelope
		input_msg = receive_message()
		
		//Copy contents of input buffer to message envelope
		int i =0; 
		For (i, i<in_buffer->count, i++)
		{
			*(input_msg->message_text + i)  = *(in_buffer->data + i) 
		}
		
		//send message to process that requested input
		input_msg ->receiver_pid = msg_input->sender_pid;
		input_msg ->sender_pid = kb_i_proc
		input_msg ->msg_type = CONSOLE_INPUT
		input_msg->msg_size = in_buffer->count;
		int send_message( input_msg->receiver_pid, input_msg )
	}	
//If user is not waiting for kb input then discard contents of buffer
//Discard contents of buffer after forwarding user input also
in_buffer->count = 0;
in_buffer->flag = 0;
		
//Restore context of interrupted process
current_process = prev_process
context_switch(pid_to_PCB_ptr(key_i_proc), current_process);
}


