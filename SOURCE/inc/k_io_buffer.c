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

struct io_buffer{
	char bufdata[BUFFER_SIZE];
	int length = 0;
	int wait_flag = 0;
};


