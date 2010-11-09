#ifndef PCB_H
#define PCB_H

#include <stdlib.h>

typedef struct k_PCB_struct *k_PCB_ptr;

typedef struct k_PCB_struct 
{
	k_PCB_ptr k_queue_next;
	k_PCB_ptr k_all_queue_next;
	//MsgEnvQ p_received_MsgEnvQ;
	int p_pid ;
	int p_priority;
	int p_status;
	//void *p_sp;
	//jmp_buf *p_jmpbuf;
} k_PCB;

#endif
