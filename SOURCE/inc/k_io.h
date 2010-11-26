#ifndef K_IO_H
#define K_IO_H

#include <stdlib.h>
#include "k_message.h"
#include "k_ipc.h"

/****************************************************************
 I/O primitives:
 Defines the functions to send and recieve I/O requests 
 ----------------------------------------------------------------

/*************************
* Function Declarations
*************************/

int k_get_console_chars (k_message_ptr key_in);

int k_send_console_chars (k_message_ptr crt_out);

#endif
