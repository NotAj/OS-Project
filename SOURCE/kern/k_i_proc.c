#include "k_i_proc.h" 

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
void k_key_i_proc()
{
	k_message_ptr input_msg;
	extern k_PCB_ptr k_interrupted_process;
	extern k_PCB_ptr k_current_process;
	extern k_io_buffer_ptr k_input_buf;

	while (1) //loop forever
	{
		//Only forward the kb input if there is a process that wants kb input (signified 
		//by a msg in the received message queue
		if (k_current_process->k_received_message_queue->head != NULL)
		{
			//receive message envelope
			input_msg = k_receive_message();
		
			//Copy contents of input buffer to message envelope
			int i; 
			for (i =0; i<k_input_buf->length; i++)
			{
				input_msg->msg_text[i]  = k_input_buf->bufdata[i]; 
			}
			//send message to process that requested input
			input_msg->receiver_pid = input_msg->sender_pid;
			input_msg->sender_pid = PID_I_KB;
			input_msg->msg_type = MSG_TYPE_CONSOLE_INPUT;
			input_msg->msg_size = k_input_buf->length;
			k_send_message (input_msg->receiver_pid, input_msg);
		}	

		//If user is not waiting for kb input then discard contents of buffer
		//Discard contents of buffer after forwarding user input also
		k_input_buf->length = 0;
		//flag of 1 means i-process is to run. O means helper is to run		
		k_input_buf->wait_flag = 0;
		
		//Restore context of interrupted process
		k_context_switch(k_current_process, k_interrupted_process);
	}
}


/****************************************************************************
* Function      : crt_i_proc 
******************************************************************************
* Description   : The crt iprocess is triggered by a signal sent from the crt helper 
*		: process every 100msec. the iprocess receives output from processes 
*		: and writes the bufdata to the output shared memory buffer. The 
*		: iprocess checks for a message in its message received queue, 
*		: and if there is it will attempt to copy the message to the output 
*		: buffer. If the shared memory is busy, it switches back to the the 
*		: interrupted process and waits until the next signal from the crt helper process.
*		           
* Assumptions   : 
*
*****************************************************************************/
void k_crt_i_proc()
{
	k_message_ptr output_msg;
	extern k_PCB_ptr k_current_process;
	extern k_PCB_ptr k_interrupted_process;
	extern k_io_buffer_ptr k_output_buf;

	while (1) //loop forever
	{
		//Check if bufdata is waiting to be output to crt
		if (!k_message_queue_is_empty(k_current_process->k_received_message_queue))
		{
			//flag of 1 means i-process is to run. O means helper is to run			
			if (k_output_buf->wait_flag == 1)
			{
				output_msg = k_receive_message();
				//write to output buffer
				int i; 
		/*		for (i=0; i<output_msg->msg_size; i++)
				{
					k_output_buf->bufdata[i]  = output_msg->msg_text[i]; 
				}
		*/		k_output_buf->length = sprintf(k_output_buf->bufdata, "%s", output_msg->msg_text);
				//send message to process that requested input
				output_msg->receiver_pid = output_msg->sender_pid;
				output_msg->sender_pid = PID_I_CRT;
				output_msg->msg_type = MSG_TYPE_DISPLAY_ACK;
				output_msg->msg_size = 0;
				k_send_message(output_msg->receiver_pid, output_msg);
				k_output_buf->wait_flag = 0;
			}
		}	
		// Restore context of interrupted process
		k_context_switch(k_current_process, k_interrupted_process);
	}
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
void k_timer_i_proc()
{
	k_timeout_queue timeoutQ;    //use global timeoutQ
	(&timeoutQ)->head = NULL;
	extern long k_clock_tick;	
	extern k_PCB_ptr k_current_process;
	extern k_PCB_ptr k_interrupted_process;
	k_message_ptr timeout_msg;
 
	while(1) //loop forever	
	{
		//update RTX internal time stamp clock
		k_clock_tick++;

		//Check if there are any new timeout request messages
		while(k_current_process->k_received_message_queue->head != NULL)  //retrieve all delay requests
			k_timeout_queue_enqueue(receive_message(), &timeoutQ);  //enqueue received message onto local TQ
		
		//If timeout queue has timeout requests
		if((&timeoutQ)->head != NULL)
			(&timeoutQ)->head->expiry_time--; //decrement

		timeout_msg = k_timeout_queue_dequeue(&timeoutQ);			
		while(timeout_msg != NULL)
		{
			//Send a timeout complete message 
			timeout_msg->receiver_pid = timeout_msg->sender_pid;
			timeout_msg->sender_pid = PID_I_TIMER;
			k_send_message(timeout_msg->receiver_pid, timeout_msg);
			timeout_msg = k_timeout_queue_dequeue(&timeoutQ);				
		}
		//Restore context of interrupted process
		k_context_switch(k_current_process, k_interrupted_process);
	}
}


