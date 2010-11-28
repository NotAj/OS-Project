#ifndef K_SYSTEM_PROC_H
#define K_SYSTEM_PROC_H

#include "k_pcb.h"
#include "k_queue.h"
#include "k_priority_queue.h"
#include "k_scheduler.h"
#include "k_message.h"
#include "k_message_queue.h"
#include "k_tracebuffer.h"
#include "api.h"
#include "k_globals.h"

void proc_null();

void proc_wall_clock();

void proc_CCI();
#endif
