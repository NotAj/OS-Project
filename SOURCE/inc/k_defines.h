#ifndef K_DEFINES_H
#define K_DEFINES_H

/***************************************
 Message Envelope Defines
****************************************/
#define MSG_ENV_SIZE 2048	// Size of the Message Envelope data field (bytes)
#define MSG_ENV_NUM 25 		// Number of Message Envelopes

/***************************************
 Process Defines
****************************************/
#define PROCESS_NUM 11 		// Number of processes in the RTX 
#define STACK_SIZE 16384	// Size of the stack for each process (16K)
#define STACK_OFFSET 8		// Offset required to set stack_pointer inside allocated memory space (Set sp to STACK_SIZE + pointer, since stack is descending, but that points just outside the stack. 8 bits is the size of 1 pointer in a 64bit system. 
#define PRIORITY_NUM 4 		// Number of priority levels in the OS

/***************************************
 IO Helper Defines
****************************************/
#define BUFFER_SIZE 2048	// Size of the shared IO buffers. Has to match Msg size

/***************************************
 Tracebuffer Defines
****************************************/
#define TRACEBUFFER_SIZE 16 // Number of traces

/***************************************
 PID Defines
****************************************/
#define PID_NULL 0 			// PID of NULL process
#define PID_WALL_CLOCK 10 	// PID of Wall Clock process
#define PID_CCI 11 			// PID of CCI Process
#define PID_I_TIMER 12 		// PID of Timer iprocess
#define PID_I_CRT 13 		// PID of CRT iprocess
#define PID_I_KB 14 		// PID of KB iprocess
#define PID_USER_A 1		// PID of User Process A
#define PID_USER_B 2		// PID of User Process B
#define PID_USER_C 3		// PID of User Process C
#define PID_USER_D 4		// PID of User Process D
#define PID_USER_E 5		// PID of User Process E
#define PID_USER_F 6		// PID of User Process F
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
#define MSG_TYPE_DISPLAY_ACK 4		// Used by CRT iprocess
#define MSG_TYPE_COUNT_REPORT 5 	// Used by User Process A
#define MSG_TYPE_WAKEUP_10 6		// Used by User Process C
#define MSG_TYPE_WALLCLOCK_DELAY 7 	// Used by Wallclock process

/***************************************
 ERROR Type Defines
****************************************/
#define ERROR_NONE 0
#define ERROR_INVALID_PARAMETERS 1
#define ERROR_MALLOC_FAILED 2
#define ERROR_CRITICAL 3
#define ERROR_CONTEXT_SWITCH 4
#define ERROR_SCHEDULING_QUEUE 5

#endif
