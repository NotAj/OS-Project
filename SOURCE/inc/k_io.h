#ifndef K_IO_H
#define K_IO_H

#include <stdlib.h>
#include "k_message.h"

/****************************************************************
 I/O primitives:
 Defines the functions to send and recieve I/O requests 
 ----------------------------------------------------------------

/*************************
* Function Declarations
*************************/

int get_console_chars (k_message_ptr key_in);

int send_console_chars (k_message_ptr crt_out);

#endif
