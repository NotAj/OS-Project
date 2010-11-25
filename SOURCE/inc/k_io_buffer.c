#ifndef K_IO_BUFFER_C
#define K_IO_BUFFER_C

#include "k_defines.h"

/****************************************************************
 IO Buffer Data structure
 ----------------------------------------------------------------
 This structure is used to store data that is being inputted from 
 the keyboard helper or outputted from the crt helper.  

 It includes a character array of size BUFFER_SIZE, a length counter
 and a flag.

*****************************************************************/
/***************************
* Type Declarations
****************************/

typedef struct k_io_buffer_struct *k_io_buffer_ptr;

typedef struct k_io_buffer_struct
{
	char bufdata[BUFFER_SIZE];
	int length;
	int wait_flag;
} k_io_buffer;

#endif
