#ifndef DEFINES_H
#define DEFINES_H

/***************************************
 Message Envelope Defines
****************************************/
#define MSG_ENV_SIZE 256 	// Size of the Message Envelope data field (bytes)
#define MSG_ENV_NUM 50 		// Number of Message Envelopes

/***************************************
 Process Defines
****************************************/
#define PROCESS_NUM 11 		// Number of processes in the RTX 
#define STACK_SIZE 1024		// Size of the stack for each process (in Bytes)

/***************************************
 IO Helper Defines
****************************************/
#define BUFFER_SIZE 512		// Size of the shared IO buffers

/***************************************
 PID Defines
****************************************/
#define PID_NULL 0 			// PID of NULL process
#define PID_WALL_CLOCK 10 	// PID of Wall Clock process
#define PID_CCI 11 			// PID of CCI Process
#define PID_I_TIMER 12 		// PID of Timer iprocess
#define PID_I_CRT 13 		// PID of CRT iprocess
#define PID_I_KB 14 		// PID of KB iprocess

/***************************************
 Status Defines
****************************************/
#define STATUS_EXECUTING 0				// Status when executing
#define STATUS_READY 1					// Status when ready
#define STATUS_BLOCKED_ON_RECEIVE 2		// Status when blocked on receive
#define STATUS_BLOCKED_ON_RESOURCE 3	// Status when blocked on resource
#define STATUS_INTERRUPTED 4			// Status when interrupted
#define STATUS_IPROCESS 5				// Status if iprocess

/***************************************
 Message Type Defines
****************************************/
#define MSG_TYPE_OUTPUT_REQUEST 0	// Used by send_console_chars()
#define MSG_TYPE_INPUT_REQUEST 1	// Used by get_console_chars()
#define MSG_TYPE_CONSOLE_INPUT 2	// Used by KB iprocess
#define MSG_TYPE_WAKEUP_CODE 3		// Used by Timer iprocess

#endif
