#include "k_i_proc.h" 
#include "k_messages.h"
#include "k_pcb.h"
#include "k_ipc.h"
#include "k_struct_init.h"
#include "k_scheduler.h"

/****************************************************************************
* Function      : key_i_proc 
******************************************************************************
* Description   : Keyboard I process only forwards user input if there is a message 
*		: in its message received queue. It works with the get_console_chars() 
*		: command, and assumes that if any process wants user input, it 
*		: has called this primitive and the primitive has sent a message 
*		: envelope to the kb i-process. The kb I process, takes this message, 
*		: populates it with user input and sends it back to the sender. 
*		           
* Assumptions   : 
*
*****************************************************************************/

void key_i_proc()
{
	k_PCB_ptr prev_process;
	k_message_ptr input_msg;
	extern k_queue_ptr k_allQ;
	extern k_PCB_ptr k_current_process;
	extern io_buffer in_buffer;

	while (1) //loop forever
	{
		//save interrupted process
		prev_process = k_current_process;
		
		//set iprocess as current process
		k_current_process = pid_to_PCB_ptr(PID_I_KB , k_allQ);
		
		//Only forward the kb input if there is a process that wants kb input (signified 
		//by a msg in the received message queue
		if (k_current_process->k_received_message_queue->head != NULL)
		{
			//receive message envelope
			input_msg = k_receive_message();
		
			//Copy contents of input buffer to message envelope
			int i; 
			for (i =0; i<in_buffer->count; i++)
			{
				input_msg->msg_text[i]  = in_buffer->data[i]; 
			}
		
			//send message to process that requested input
			input_msg->receiver_pid = input_msg->sender_pid;
			input_msg->sender_pid = PID_I_KB;
			input_msg->msg_type = MSG_TYPE_CONSOLE_INPUT;
			input_msg->msg_size = in_buffer->count;
			k_send_message (input_msg->receiver_pid, input_msg);
		}	

		//If user is not waiting for kb input then discard contents of buffer
		//Discard contents of buffer after forwarding user input also
		in_buffer->count = 0;
		in_buffer->flag = 0;
		
		//Restore context of interrupted process
		k_current_process = prev_process;
		k_context_switch(pid_to_PCB_ptr(PID_I_KB, k_allQ), k_current_process);
	}
}


/****************************************************************************
* Function      : crt_i_proc 
******************************************************************************
* Description   : The crt iprocess is triggered by a signal sent from the crt helper 
*		: process every 100msec. the iprocess receives output from processes 
*		: and writes the data to the output shared memory buffer. The 
*		: iprocess checks for a message in its message received queue, 
*		: and if there is it will attempt to copy the message to the output 
*		: buffer. If the shared memory is busy, it switches back to the the 
*		: interrupted process and waits until the next signal from the crt helper process.
*		           
* Assumptions   : 
*
*****************************************************************************/


void crt_i_proc()
{
	k_PCB_ptr prev_process;
	k_message_ptr output_msg;
	extern k_queue_ptr k_allQ;
	extern k_PCB_ptr k_current_process;
	extern io_buffer out_buffer;

	while (1) //loop forever
	{
		//save interrupted process
		prev_process = k_current_process;
		//set iprocess as current process
		k_current_process = pid_to_PCB_ptr(PID_I_CRT, k_allQ);

		//Check if data is waiting to be output to crt
		if (k_current_process->k_received_message_queue->head != NULL)
		{
			if (out_buffer->flag == 1)
			{
				output_msg = k_receive_message();
				//write to output buffer
				int i; 
				for (i=0; i<output_msg->msg_size; i++)
				{
					out_buffer->data[i]  = output_msg->msg_text[i]; 
				}
				out_buffer->count = output_msg->msg_size;
				out_buffer->flag = 0;
			}
		
			//send message to process that requested input
			output_msg->receiver_pid = msg_input->sender_pid;
			output_msg->sender_pid = PID_I_CRT;
			output_msg->msg_type = MSG_TYPE_DISPLAY_ACK;
			output_msg->msg_size = 0;
			k_send_message(output_msg->receiver_pid, output_msg)
		}	
	}
	//Restore context of interrupted process
	k_current_process = prev_process;
	k_context_switch(pid_to_PCB_ptr(PID_I_CRT, k_allQ), k_current_process);
}

/****************************************************************************
* Function      : timer_i_proc 
******************************************************************************
* Description   : The timer i-process is triggered every 100 ms by the Interrupt 
*		: Handler. The enqueues any new timeout requests into a local queue.
*		: Then the queue is traversed and the time remaining on each timeout 
*		: is decremented by 1 tick (100ms). The process then checks to see 
*		: whether any of the request are now complete (time remaining <= 0). 
*		: If a request is complete, the same message is sent back to the 
*		: requesting process. The message envelope is then dequeued from the local queue.
*		           
* Assumptions   : 
*
*****************************************************************************/

void timer_i_proc()
{
	extern k_timeout_queue TQ;    //use global timeoutQ
	extern int k_clock_tick;	
	extern k_PCB_ptr k_current_process;
	k_PCB_ptr prev_process;
	k_message_ptr timeout_msg;
 
	while(1) //loop forever	
	{
		//save interrupted process
		prev_process = current_process;
		//set iprocess as current process
		current_process = pid_to_PCB_ptr(PID_I_TIMER, k_allQ);

		//update RTX internal time stamp clock
		k_clock_tick++;

		//Check if there are any new timeout request messages
		while(k_current_process->p_received_MsgEnvQ->head != NULL)  //retrieve all delay requests
			k_timeout_queue_enqueue(receive_message(), TQ);  //enqueue received message onto local TQ
		
		//If timeout queue has timeout requests
		if(TQ->head != NULL)
			TQ->head->expiry-time--; //decrement

		timeout_msg = k_timeout_queue_dequeue(TQ);			
		while(timeout_msg != NULL)
		{
			//Send a timeout complete message 
			timeout_msg->receiver_pid = timeout_input->sender_pid;
			timeout_msg->sender_pid = timer_i_proc;
			timeout_msg->msg_type = MSG_TYPE_WAKEUP_CODE;
			timeout_msg->msg_size = 0;
			k_send_message( timeout_msg->receiver_pid, timeout_msg);
			timeout_msg = k_timeout_queue_dequeue(TQ);				
		}
		//Restore context of interrupted process
		k_current_process = prev_process;
		k_context_switch(pid_to_PCB_ptr(PID_I_TIMER, k_allQ), k_current_process);
	}
}


