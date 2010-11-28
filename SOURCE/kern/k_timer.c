#include "k_timer.h"

/***************************************************************************
* Function      : k_request_delay 
****************************************************************************
* Description   : This function is used to send a delay request to the timer
*				: iprocess by specifying the time_delay in number of 100msec
*				: intervals. The caller can specify the wake up code that will
*				: be provided in the message type field once the delay is complete. 
*              
* Assumptions   : A valid MsgEnv * must have been previously requested and supplied.
*****************************************************************************/
int k_request_delay (int time_delay, int wakeup_code, MsgEnv *message_envelope)
{
	message_envelope->msg_type = wakeup_code;
	message_envelope->expiry_time = time_delay;
	message_envelope->msg_size = 0;
	k_send_message(PID_I_TIMER, message_envelope);
	return ERROR_NONE;
}


