#include "k_init_struct.h"

k_PCB_ptr k_PCB_init(int p_pid, int p_status, int p_priority, void *k_start_address)
{	
	// Initialize PCB
	k_PCB_ptr PCB = (k_PCB_ptr) malloc(sizeof(k_PCB));
	
	if (PCB == NULL)
		return NULL; // Return NULL if malloc failed
	
	// Check if priority is valid, if not set to lowest priority
	if (p_priority < 0 || p_priority >= PRIORITY_NUM)
		p_priority = PRIORITY_NUM - 1;
	
	// Set fields of PCB
	PCB->k_queue_next = NULL;
	PCB->k_all_queue_next = NULL;
	PCB->k_received_message_queue = k_message_queue_init();
	PCB->p_pid = p_pid;
	PCB->p_status = p_status;
	PCB->p_priority = p_priority;
	PCB->k_start_address = k_start_address;
	PCB->k_stack_pointer = NULL;
	
	return PCB;
}

k_message_ptr k_message_init()
{
	// Allocate space for message envelope fields and text field.
	k_message_ptr msg= (k_message_ptr) malloc(sizeof(k_message));
	msg->msg_text = (char *) malloc(sizeof(char) * MSG_ENV_SIZE);
	return msg;
}	

k_queue_ptr k_queue_init()
{
	// Return pointer to allocated queue
	k_queue_ptr Q = (k_queue_ptr) malloc(sizeof(k_queue));
	if (Q == NULL)
		return NULL; // If malloc failed, return NULL pointer
	Q->tail = NULL;
	Q->head = NULL;
	return Q;
}

k_priority_queue_ptr k_priority_queue_init()
{
	k_priority_queue_ptr PQ = (k_priority_queue_ptr) malloc(sizeof(k_priority_queue));
	if (PQ == NULL)
		return NULL; // If malloc failed return NULL pointer
	int i, j;
	// Allocate space for all structs in the array (4 queues)
	for (i=0; i< PRIORITY_NUM; i++)
	{
		PQ->array[i] = (k_queue_ptr) malloc(sizeof(k_queue));
		if (PQ->array[i] == NULL) 
		{
			// If malloc failed, free all allocated memory and return NULL pointer.
			for (j=0; j<i ; j++)
				free(PQ->array[j]);
			free(PQ);
			return NULL;
		}		
		PQ->array[i]->head = NULL;
		PQ->array[i]->tail = NULL; 
	}
	return PQ;
}

k_message_queue_ptr k_message_queue_init()
{
	k_message_queue_ptr MQ = (k_message_queue_ptr) malloc(sizeof(k_message_queue));
	if (MQ == NULL)	
		return NULL; // If malloc failed, return NULL pointer
	MQ->head = NULL;
	MQ->tail = NULL;
	return MQ;
}

k_tracebuffer_ptr k_tracebuffer_init()
{
	k_tracebuffer_ptr TB = (k_tracebuffer_ptr) malloc(sizeof(k_tracebuffer));
	if (TB == NULL)
		return NULL; // If malloc failed return NULL pointer
	int i, j;
	// Allocate space for all structs in the array (16 traces)
	for (i=0; i< TRACEBUFFER_SIZE; i++)
	{
		TB->buffer[i] = malloc(sizeof(k_trace));
		if (TB->buffer[i] == NULL) 
		{
			// If malloc failed, free all allocated memory and return NULL pointer.
			for (j=0; j<i ; j++)
				free(TB->buffer[j]);
			free(TB);
			return NULL;
		}		
		TB->buffer[i]->sender_pid = 0; 
		TB->buffer[i]->receiver_pid = 0; 
		TB->buffer[i]->msg_type = 0; 
		TB->buffer[i]->timestamp = 0; 
	}
	TB->head = 0; // TB->head can be initialized to any value, pick 0
	return TB;
}

k_itable_ptr k_itable_init(int process_num, int *pid, int *priority, int *is_iprocess, void **start_address)
{
	int i;
	k_itable_ptr process_table = malloc(sizeof(k_itable));
	process_table->pid = malloc(sizeof(int) * process_num);
	process_table->priority = malloc(sizeof(int) * process_num);
	process_table->is_iprocess = malloc(sizeof(int) * process_num);
	process_table->start_address = malloc(sizeof(void *) * process_num);
	for (i=0; i<process_num; i++)
	{
		process_table->pid[i] = pid[i];
		process_table->priority[i] = priority[i];
		process_table->is_iprocess[i] = is_iprocess[i];
		process_table->start_address[i] = start_address[i];
	} 
	return process_table;
}

k_io_buffer_ptr k_io_buffer_init()
{
	k_io_buffer_ptr myBuff = (k_io_buffer_ptr)malloc(sizeof(k_io_buffer));
	myBuff->bufdata = (char *)malloc(BUFFER_SIZE*sizeof(char));
	myBuff->length = 0;
	myBuff->wait_flag = 0;
	return myBuff;
}
