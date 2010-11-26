#include "k_defines.h"
#include "k_globals.h"
#include "k_init.h"
#include "k_init_struct.h"
#include "k_io_buffer.c"
#include "k_i_proc.h"
#include "k_pcb.h"
#include "k_utility.h"
#include "k_message.h"
#include "k_message_queue.h"
#include "k_pcb.h"
#include <stdio.h>
#include <assert.h>


int main()
{
		
	extern k_PCB_ptr k_current_process;

	printf("TESTING KEYBOARD-I-PROCESS \n");

	extern k_io_buffer_ptr input_buf;
	input_buf = k_io_buffer_init();
	assert(input_buf != NULL);	
	
	//fake input buffer data	
	int i;
	for (i=0; i<=19; i++) 	
		input_buf->bufdata[i] = i;	
	input_buf->length = 20;
	input_buf->wait_flag = 1;			
	
	//insert fake pointer in recieved message queue
	k_message_ptr input_msg;	
	input_msg = k_message_init();	
	k_current_process = k_pid_to_PCB_ptr(PID_I_KB);
	k_current_process->k_received_message_queue->head = input_msg;
	input_msg->k_queue_next = NULL;
	input_msg->sender_pid = 44;
	
	//print buffer  info
	printf("before the process buffer contains: \n");
	printf("buffer_length = %d \n", input_buf->length);
	printf("buffer_wait_flag = %d \n", input_buf->wait_flag);
	
	printf("buffer_data = ");	
	for (i=0; i<input_buf->length; i++)	
		printf("%c ", input_buf->bufdata[i]);
	printf("\n\n");

	//call i-process	
	k_key_i_proc();

	//print buffer  info
	printf("after the process buffer contains: \n");
	printf("buffer_length = %d \n", input_buf->length);
	printf("buffer_wait_flag = %d \n", input_buf->wait_flag);
	printf("buffer_data = ");	
	for (i=0; i<input_buf->length; i++)	
		printf("%c ", input_buf->bufdata[i]);
	printf("\n\n");

	//print message info
	printf("the message to be sent contains: \n");
	printf("message_size = %d \n", input_msg->msg_size);
	printf("message_type = %d \n", input_msg->msg_type);	
	printf("message_sender_pid = %d \n", input_msg->sender_pid);
	printf("message_receiver_pid = %d \n", input_msg->receiver_pid);
	printf("message_data = ");	
	for (i=0; i<input_msg->msg_size; i++)	
		printf("%c ", input_msg->msg_text[i]);
	printf("\n\n");

//////////////////////////////////////////////////////////////////////////////////
	printf("TESTING CRT-I-PROCESS \n");

	extern k_io_buffer_ptr output_buf;
	output_buf = k_io_buffer_init();
	assert(output_buf != NULL);	
	
	k_message_ptr output_msg;	
	output_msg = k_message_init();	
	
	//fake output message data	
	for (i=0; i<=19; i++) 	
		output_msg->msg_text[i] = i;	
	output_msg->msg_size = 20;
	output_msg->sender_pid = 44;			
	
	//insert fake pointer in recieved message queue
	k_current_process = k_pid_to_PCB_ptr(PID_I_CRT);
	k_current_process->k_received_message_queue->head = output_msg;
	output_msg->k_queue_next = NULL;
	
	//create empty buffer
	output_buf->length = 0;
	output_buf->wait_flag = 1;	

	//print buffer  info
	printf("before the process buffer contains: \n");
	printf("buffer_length = %d \n", output_buf->length);
	printf("buffer_wait_flag = %d \n", output_buf->wait_flag);
		printf("buffer_data = ");	
	for (i=0; i<output_buf->length; i++)	
		printf("%c ", output_buf->bufdata[i]);
	printf("\n\n");

	//print message info
	printf("the message to be output contains: \n");
	printf("message_size = %d \n", output_msg->msg_size);
	printf("message_sender_pid = %d \n", output_msg->sender_pid);
	printf("message_data = ");	
	for (i=0; i<output_msg->msg_size; i++)	
		printf("%c ", output_msg->msg_text[i]);
	printf("\n\n");

	//call i-process	
	k_crt_i_proc();

	//print buffer  info
	printf("after the process buffer contains: \n");
	printf("buffer_length = %d \n", output_buf->length);
	printf("buffer_wait_flag = %d \n", output_buf->wait_flag);
	printf("buffer_data = ");	
	for (i=0; i<output_buf->length; i++)	
		printf("%c ", output_buf->bufdata[i]);
	printf("\n\n");

	//print message info
	printf("the message to be sent contains: \n");
	printf("message_size = %d \n", output_msg->msg_size);
	printf("message_type = %d \n", output_msg->msg_type);	
	printf("message_sender_pid = %d \n", output_msg->sender_pid);
	printf("message_receiver_pid = %d \n", output_msg->receiver_pid);
	printf("message_data = ");	
	for (i=0; i<output_msg->msg_size; i++)	
		printf("%c ", output_msg->msg_text[i]);
	printf("\n\n");

///////////////////////////////////////////////////////////////////////////////	
	printf("TESTING TIMER-I-PROCESS \n");
	
	extern int k_clock_tick;	
	k_message_ptr timeout_msg;	
	timeout_msg = k_message_init();	

	k_clock_tick = 0;
	//fake output message data	
	timeout_msg->receiver_pid = PID_I_TIMER;
	timeout_msg->sender_pid = 44;	
	timeout_msg->expiry_time = 4;		
	
	//insert fake pointer in recieved message queue
	k_current_process = k_pid_to_PCB_ptr(PID_I_TIMER);
	k_current_process->k_received_message_queue->head = timeout_msg;
	timeout_msg->k_queue_next = NULL;
	
	//print message info
	printf("the message to be timedout contains: \n");
	printf("message_expiry = %d \n", timeout_msg->expiry_time);
	printf("message_sender_pid = %d \n", timeout_msg->sender_pid);
	printf("message_receiver_pid = %d \n", timeout_msg->receiver_pid);

	//call i-proc
	k_timer_i_proc();
	
	//print message info
	printf("the message to be timedout contains: \n");
	printf("message_expiry = %d \n", timeout_msg->expiry_time);
	printf("message_sender_pid = %d \n", timeout_msg->sender_pid);
	printf("message_receiver_pid = %d \n", timeout_msg->receiver_pid);

	//call i-proc
	k_timer_i_proc();
	
	//print message info
	printf("the message to be timedout contains: \n");
	printf("message_expiry = %d \n", timeout_msg->expiry_time);
	printf("message_sender_pid = %d \n", timeout_msg->sender_pid);
	printf("message_receiver_pid = %d \n", timeout_msg->receiver_pid);

	//call i-proc
	k_timer_i_proc();
	
	//print message info
	printf("the message to be timedout contains: \n");
	printf("message_expiry = %d \n", timeout_msg->expiry_time);
	printf("message_sender_pid = %d \n", timeout_msg->sender_pid);
	printf("message_receiver_pid = %d \n", timeout_msg->receiver_pid);

	//call i-proc
	k_timer_i_proc();
	
	//print message info
	printf("the message to be timedout contains: \n");
	printf("message_expiry = %d \n", timeout_msg->expiry_time);
	printf("message_sender_pid = %d \n", timeout_msg->sender_pid);
	printf("message_receiver_pid = %d \n", timeout_msg->receiver_pid);
	printf("message_msg_type = %d \n", timeout_msg->msg_type);
	printf("clock time is = %d \n", k_clock_tick);	
}
















