#include "k_io.h"
#include "k_defines.h"
#include "k_globals.h"
#include "k_message.h"
#include "k_ipc.h"

/****************************************************************
 I/O FUNCTIONS
 ----------------------------------------------------------------
 Functions that help the user proccesses send out put and recieve input 

*****************************************************************/

/****************************************************************************
* Function      : k_get_console_chars
******************************************************************************
* Description   : This function takes a messaage envelope from the requesting process 
*				: and sends it empty to the kbd i-process to be returned with input
*           
* Assumptions   : 
*****************************************************************************/
int k_get_console_chars (k_message_ptr key_in)
{
	if (key_in == NULL) //check null case
		return ERROR_INVALID_PARAMETERS;	
	//initialize message fields for input request
	key_in->msg_type = MSG_TYPE_INPUT_REQUEST;
	key_in->msg_size = 0;
	k_send_message(PID_I_KB, key_in);
	return ERROR_NONE;
}

/****************************************************************************
* Function      : k_send_console_chars
******************************************************************************
* Description   : This function takes a messaage envelope from the requesting process 
*				: and sends the message to be output to the crt i-process
*           
* Assumptions   : 
*****************************************************************************/
int k_send_console_chars (k_message_ptr crt_out)
{
	if (crt_out == NULL)
		return ERROR_INVALID_PARAMETERS;
	//initialize message fields for output request
	crt_out->msg_type = MSG_TYPE_OUTPUT_REQUEST;
	crt_out->msg_size = 0;
	while (crt_out->msg_text[crt_out->msg_size] != '\0')
		crt_out->msg_size++;
	k_send_message(PID_I_CRT, crt_out);
	return ERROR_NONE;
}

