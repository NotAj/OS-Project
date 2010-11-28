#ifndef K_IO_H
#define K_IO_H

#include <stdlib.h>
#include "k_message.h"
#include "k_ipc.h"
#include "k_globals.h"

/****************************************************************
 I/O FUNCTIONS
 ----------------------------------------------------------------
 Functions that help the user proccesses send out put and recieve input 

*****************************************************************/

/*************************
* Function Declarations
*************************/
int k_get_console_chars (k_message_ptr key_in);

int k_send_console_chars (k_message_ptr crt_out);

#endif
