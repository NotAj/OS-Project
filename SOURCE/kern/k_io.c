#include "k_io.h"
#include "k_defines.h"
#include "k_globals.h"
#include "k_message.h"

/****************************************************************
 I/O FUNCTIONS
 ----------------------------------------------------------------
Functions that help the user proccesses send out put and recieve input 

*****************************************************************/

/****************************************************************************
* Function      : get_console_chars
******************************************************************************
* Description   : This function takes a messaage envelope from the requesting process 
*		: and sends it empty to the Keyboard i-process to be returned with input
*           
* Assumptions   : 
*****************************************************************************/

int get_console_chars (k_message_ptr key_in)
{
	if (key_in == NULL) //check null case
		return 0;	
	//initialize message fields for input request
	key_in->receiver_pid = PID_I_KB; 	
	extern k_PCB_ptr k_current_process;	
	key_in->sender_pid = k_current_process->p_pid;		
	key_in->msg_type = MSG_TYPE_INPUT_REQUEST;
	key_in->msg_size = 0;
	//send_message(key_in->receiver_pid, key_in);
	return 1;
}


/****************************************************************************
* Function      : send_console_chars
******************************************************************************
* Description   : This function takes a messaage envelope from the requesting process 
*		: and sends the message to be output to the crt i-process
*           
* Assumptions   : 
*****************************************************************************/

int send_console_chars (k_message_ptr crt_out)
{
	if (crt_out == NULL)
		return 0;
	//initialize message fields for output request
	crt_out->receiver_pid = PID_I_CRT;
	extern k_PCB_ptr k_current_process;	
	crt_out->sender_pid = k_current_process->p_pid;
	crt_out->msg_type = MSG_TYPE_OUTPUT_REQUEST;
	crt_out->msg_size = 0;
	while (crt_out->msg_text[crt_out->msg_size] != '\0')
		crt_out->msg_size++;
	//send_message(crt_out->receiver_pid, crt_out)
	return 1;

}

