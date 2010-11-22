#ifndef K_ITABLE_C
#define K_ITABLE_C

/****************************************************************
  Itable Data structure
 ----------------------------------------------------------------
 The itable is used to hold information on all processes in the RTX,
 and used during initialization to set up the PCBs of all processes. 

*****************************************************************/

/*************************
* Type Declarations
*************************/
typedef struct k_itable_struct *k_itable_ptr;

// Itable consists of 4 fields that will be copied to PCBs, full itable is array of these.
typedef struct k_itable_struct
{	
	int *pid;
	int *priority;
	int *is_iprocess;
	void **start_address;
} k_itable;

/*************************
* Function Declarations
*************************/
#endif
