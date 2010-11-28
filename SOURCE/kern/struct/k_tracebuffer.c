#include "k_tracebuffer.h"

/****************************************************************
 Tracebuffer Data Structure 
 ----------------------------------------------------------------
 This structure is used to trace the sending and receiving of 
 messages between processes. The tracebuffer contains the PID of
 the sender and receiver, as well as the type of message and the 
 system time at which it was sent or received. This functionality 
 is included in the send_message and receive_message functions,
 and the information is printed by the get_tracebuffer function.

*****************************************************************/

/****************************************************************************
* Function      : k_update_tracebuffer 
******************************************************************************
* Description   : This function updates the tracebuffer with the information
*				: provided. It is implemented as a circular array of 16
*				: traces, so that the oldest trace in the buffer is always 
*				: overwritten when the buffer is full. This function will 
*				: always print the entire tracebuffer, even if it is empty
*				
* Assumptions   : TB->head can be initialized to any value 
*****************************************************************************/
void k_tracebuffer_update (int sender_pid, int receiver_pid, int msg_type, k_tracebuffer_ptr TB)
{
	extern int k_clock_tick; // Get system time first

	// Decrement head, rolling over if it goes negative
	// This sets the new head to the oldest entry in the TB
	TB->head--;
	if (TB->head < 0)
		TB->head = TRACEBUFFER_SIZE - 1;

	// Populate fields of trace with supplied info
 	TB->buffer[TB->head]->sender_pid = sender_pid;
	TB->buffer[TB->head]->receiver_pid = receiver_pid;
	TB->buffer[TB->head]->msg_type = msg_type;
	TB->buffer[TB->head]->timestamp = k_clock_tick;
}



