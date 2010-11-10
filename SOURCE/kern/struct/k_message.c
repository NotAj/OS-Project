#include "k_message.h"

/****************************************************************
 Message Envelope Data structure
 ----------------------------------------------------------------
 This structure is used for all interprocess communication. Message
 Envelopes are passed back and forth between process to exchange 
 information, and to send/receive IO. For this IPC scheme it is 
 assumed that all processes know each others PID. 
 The message envelope structure contains the PID of the sender 
 and receiver and the message type. These help the receiving 
 processes figure out what to expect in the message, or know
 what process to reply to. The expiry_time field is used by
 the timer i-process and processes requesting a delay. The
 msg_size field is used to simplify reading the message contents,
 which are stored in an array of characters.

*****************************************************************/

