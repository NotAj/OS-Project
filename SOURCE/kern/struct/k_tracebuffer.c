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
*				: overwritten when the buffer is full. 
*				
* Assumptions   : TB->head is initialized to 1, TB->tail to 0 
*****************************************************************************/
void k_tracebuffer_update (int sender_pid, int receiver_pid, int msg_type, k_tracebuffer_ptr TB)
{
	int timestamp = 0; //k_clock_tick; // Get system time first
	
	// TODO Decide which scheme to use, head and tail or just head
	// Handling the initial case, By setting head 1 greater. This will make tail always 1 less than head, and print all items in the array.
	// This can be improved by using only head and size of tracebuffer.
/*	if (TB->head == TB->tail)
		TB->head++;
*/	

	// Increment head, rolling over if it goes negative
	TB->head--;
	if (TB->head < 0)
		TB->head = TRACEBUFFER_SIZE - 1;

// TODO Decide which scheme to use
/*
	if (TB->head == TB->tail) // Means the buffer is full, so overwrite oldest entry
		// Increment tail, rolling over if it goes negative
		TB->tail--;
		if (TB->tail < 0)
			TB->tail = TRACEBUFFER_SIZE - 1;
*/

	// Populate fields of trace wil supplied info
 	// NOTE: Since array is initialized by calling malloc on struct, use . to dereference as each element in the array holds the struct itself
	TB->buffer[TB->head].sender_pid = sender_pid;
	TB->buffer[TB->head].receiver_pid = receiver_pid;
	TB->buffer[TB->head].msg_type = msg_type;
	TB->buffer[TB->head].timestamp = timestamp;
}
