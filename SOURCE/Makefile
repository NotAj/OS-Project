CC = gcc
CFLAGS = -Wall -g $(INC_DIR) 
LDFLAGS = -g $(INC_DIR) 

INC_DIR = -I./inc/ -I./proc/

SOURCES = k_pcb.h k_message.h k_queue.h k_priority_queue.h k_message_queue.h k_timeout_queue.h k_tracebuffer.h k_itable.c k_io_buffer.c k_utility.h k_scheduler.h k_ipc.h k_io.h api.h k_system_proc.h k_i_proc.h user_proc.h k_init_struct.h k_init.h k_globals.h k_defines.h k_interrupt_handler.h 
HELPER_SOURCES = k_defines.h k_io_buffer.h k_init_struct.h
TEST_SOURCES = test_queue.h test_priority_queue.h test_message_queue.h test_tracebuffer.h test_timeout_queue.h

MEM_FILES = helpers/inputfile helpers/outputfile

# TODO Figure out proper way of linking using o files in obj/
OBJ_DIR = obj/
HELPER_DIR = helpers/

VPATH = inc:kern:test:kern/struct:init:proc:proc/inc:helpers:obj 
OBJECTS_INTER = $(SOURCES:.h=.o)
OBJECTS = $(OBJECTS_INTER:.c=.o)
OBJECTS_DIR = $(OBJECTS:%=$(OBJ_DIR)%) 

HELPER_OBJECTS = $(HELPER_SOURCES:.h=.o)
HELPER_OBJECTS_DIR = $(HELPER_OBJECTS:%=$(OBJ_DIR)%)

TEST_OBJECTS_INTER = $(OBJECTS) $(TEST_SOURCES:.h=.o)
TEST_OBJECTS = $(TEST_OBJECTS_INTER:.c=.o)
TEST_OBJECTS_DIR = $(TEST_OBJECTS:%=$(OBJ_DIR)%)

MAIN = main.c

CRT_MAIN = helpers/crt_helper.c
KBD_MAIN = helpers/kbd_helper.c

TEST_Q_MAIN = test/main_queue.c
TEST_PQ_MAIN = test/main_priority_queue.c
TEST_MQ_MAIN = test/main_message_queue.c
TEST_TQ_MAIN = test/main_timeout_queue.c
TEST_TB_MAIN = test/main_tracebuffer.c 
TEST_ITABLE_MAIN = test/main_itable.c 
TEST_UTILITY_MAIN = test/main_utility.c
TEST_SCHEDULER_MAIN = test/main_scheduler.c

TEST_IO_MAIN = test/main_io.c
TEST_IPC_MAIN = test/main_ipc_2.c

TEST_KBD_MAIN = test/main_kbd.c
TEST_CRT_MAIN = test/main_crt.c
TEST_IPC_MAIN = test/main_ipc.c
TEST_IH_MAIN = test/main_interrupt_handler.c
TEST_IPROC_MAIN = test/main_i_proc.c

EXE = RTX 

CRT_HELPER_EXE = crt_helper
KBD_HELPER_EXE = kbd_helper

TEST_Q_EXE = TEST_Q
TEST_PQ_EXE = TEST_PQ 
TEST_MQ_EXE = TEST_MQ
TEST_TQ_EXE = TEST_TQ
TEST_TB_EXE = TEST_TB
TEST_ITABLE_EXE = TEST_ITABLE
TEST_UTILITY_EXE = TEST_UTILITY
TEST_SCHEDULER_EXE = TEST_SCHEDULER
TEST_IPC_EXE = TEST_IPC
TEST_IO_EXE = TEST_IO
TEST_IH_EXE = TEST_IH
TEST_IPROC_EXE = TEST_IPROC

TEST_KBD_EXE = TEST_KBD
TEST_CRT_EXE = TEST_CRT

RTX_EXECUTABLES = $(EXE) $(CRT_HELPER_EXE) $(KBD_HELPER_EXE)
TEST_EXECUTABLES = $(TEST_Q_EXE) $(TEST_PQ_EXE) $(TEST_MQ_EXE) $(TEST_TQ_EXE) $(TEST_TB_EXE) $(TEST_ITABLE_EXE) $(TEST_UTILITY_EXE) $(TEST_SCHEDULER_EXE) $(TEST_IPC_EXE) $(TEST_IO_EXE) $(TEST_IH_EXE)  $(TEST_KBD_EXE) $(TEST_CRT_EXE) $(TEST_IPROC_EXE)
ALL_EXECUTABLES = $(RTX_EXECUTABLES) $(TEST_EXECUTABLES)

all: $(RTX_EXECUTABLES) 
rtx: $(RTX_EXECUTABLES)
test: $(TEST_EXECUTABLES)

$(EXE): $(OBJECTS) $(MAIN)
	$(CC) $(LDFLAGS) $(OBJECTS_DIR) $(MAIN) -o $@

$(CRT_HELPER_EXE): $(HELPER_OBJECTS) $(CRT_MAIN)
	$(CC) $(LDFLAGS) $(HELPER_OBJECTS_DIR) $(CRT_MAIN) -o $(HELPER_DIR)$@ 
$(KBD_HELPER_EXE): $(HELPER_OBJECTS) $(KBD_MAIN)
	$(CC) $(LDFLAGS) $(HELPER_OBJECTS_DIR) $(KBD_MAIN) -o $(HELPER_DIR)$@

$(TEST_Q_EXE): $(TEST_OBJECTS) $(TEST_Q_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_Q_MAIN) -o $@
$(TEST_PQ_EXE): $(TEST_OBJECTS) $(TEST_PQ_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_PQ_MAIN) -o $@
$(TEST_MQ_EXE): $(TEST_OBJECTS) $(TEST_MQ_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_MQ_MAIN) -o $@
$(TEST_TQ_EXE): $(TEST_OBJECTS) $(TEST_TQ_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_TQ_MAIN) -o $@
$(TEST_TB_EXE): $(TEST_OBJECTS) $(TEST_TB_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_TB_MAIN) -o $@
$(TEST_ITABLE_EXE): $(TEST_OBJECTS) $(TEST_ITABLE_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_ITABLE_MAIN) -o $@
$(TEST_UTILITY_EXE): $(TEST_OBJECTS) $(TEST_UTILITY_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_UTILITY_MAIN) -o $@
$(TEST_SCHEDULER_EXE): $(TEST_OBJECTS) $(TEST_SCHEDULER_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_SCHEDULER_MAIN) -o $@
$(TEST_IO_EXE): $(TEST_OBJECTS) $(TEST_IO_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_IO_MAIN) -o $@
$(TEST_IPC_EXE): $(TEST_OBJECTS) $(TEST_IPC_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_IPC_MAIN) -o $@
$(TEST_KBD_EXE): $(TEST_OBJECTS) $(TEST_KBD_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_KBD_MAIN) -o $@
$(TEST_CRT_EXE): $(TEST_OBJECTS) $(TEST_CRT_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_CRT_MAIN) -o $@
$(TEST_IH_EXE): $(TEST_OBJECTS) $(TEST_IH_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_IH_MAIN) -o $@
$(TEST_IPROC_EXE): $(TEST_OBJECTS) $(TEST_IPROC_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_IPROC_MAIN) -o $@


$(OBJECTS): | $(OBJ_DIR)
$(TEST_OBJECTS): | $(OBJ_DIR)

$(OBJ_DIR):
	@echo $(OBJECTS) 
	mkdir $(OBJ_DIR)

.c.o:
	$(CC) $(CFLAGS) -c -o $(OBJ_DIR)$@ $<
.h.o:
	$(CC) $(CFLAGS) -c -o $(OBJ_DIR)$@ $<

k_pcb.o: k_pcb.h k_defines.h
k_message.o: k_message.h k_defines.h

k_queue.o: k_queue.h k_pcb.h 
k_priority_queue.o : k_priority_queue.h k_queue.h k_pcb.h k_utility.h k_defines.h
k_message_queue.o: k_message_queue.h k_message.h
k_timeout_queue.o: k_timeout_queue.h k_message.h
k_tracebuffer.o: k_tracebuffer.h k_defines.h
k_itable.o: 
k_io_buffer.o: k_io_buffer.c

k_scheduler: k_scheduler.h k_pcb.h k_queue.h k_priority_queue.h k_globals.h
k_utility.o: k_utility.h k_pcb.h k_queue.h k_ipc.h k_defines.h k_globals.h
k_io.o: k_io.h k_defines.h k_globals.h k_message.h k_ipc.h
k_ipc.o: k_ipc.h k_scheduler.h k_pcb.h k_message_queue.h k_message.h k_tracebuffer.h k_defines.h k_utility.h

api.o: api.h k_pcb.h k_message.h k_queue.h k_priority_queue.h k_scheduler.h k_message.h k_message_queue.h k_tracebuffer.h  

k_system_proc.o: k_system_proc.h k_pcb.h k_message.h k_queue.h k_priority_queue.h k_scheduler.h k_message.h k_message_queue.h k_tracebuffer.h api.h 
k_system_proc.o: k_i_proc.h k_pcb.h k_message.h k_queue.h k_priority_queue.h k_scheduler.h k_message.h k_message_queue.h k_tracebuffer.h api.h 
user_proc.o: user_proc.h api.h
k_interrupt_handler.o: k_defines.h k_globals.h k_scheduler.h k_interrupt_handler.h k_timeout_queue.h k_utility.h
k_i_proc.o: k_pcb.h k_queue.h k_priority_queue.h k_scheduler.h k_message.h k_message_queue.h k_tracebuffer.h api.h k_globals.h k_ipc.h k_init_struct.h k_defines.h k_io_buffer.c k_timeout_queue.h k_utility.h

k_init_struct.o: k_init_struct.h k_pcb.h k_message.h k_queue.h k_priority_queue.h k_message_queue.h k_tracebuffer.h k_itable.c
k_init.o: k_init.h k_pcb.h k_message.h k_queue.h k_priority_queue.h k_message_queue.h k_tracebuffer.h k_itable.c k_init_struct.h k_system_proc.h k_i_proc.h user_proc.h k_defines.h k_globals.h

k_globals.o: k_globals.h k_pcb.h k_message.h k_queue.h k_priority_queue.h k_message_queue.h k_tracebuffer.h k_init_struct.h
k_defines.o: k_defines.h k_pcb.h 

test_queue.o: k_queue.h k_pcb.h k_init_struct.h
test_priority_queue.o: test_priority_queue.h k_priority_queue.h k_init_struct.h
test_message_queue.o: test_message_queue.h k_message_queue.h k_init_struct.h
test_timeout_queue.o: test_timeout_queue.h k_timeout_queue.h
test_tracebuffer.o: test_tracebuffer.h k_tracebuffer.h k_init_struct.h
test_scheduler.o: test_scheduler.h k_scheduler.h k_pcb.h k_queue.h k_priority_queue.h
test_utility.o: test_utility.h k_pcb.h k_queue.h k_defines.h k_globals.h

.PHONY: clean

clean:
	rm -f $(MEM_FILES)	
	rm -f *.o $(ALL_EXECUTABLES)
	rm -rf $(OBJ_DIR)
	rm -f $(HELPER_DIR)crt_helper $(HELPER_DIR)kbd_helper
