CC = gcc
CFLAGS = -Wall -g $(INC_DIR) 
LDFLAGS = -g $(INC_DIR) 

INC_DIR = -I./inc/ -I./proc/inc

SOURCES = k_pcb.h k_message.h k_queue.h k_priority_queue.h k_message_queue.h k_tracebuffer.h k_itable.c k_utility.h k_scheduler.h k_init_struct.h k_init.h k_globals.h k_defines.h io_buffer.c kbd_helper.c crt_helper.c

TEST_SOURCES = test_queue.h test_priority_queue.h test_message_queue.h test_tracebuffer.h 

SOURCES = k_pcb.h k_message.h k_queue.h k_priority_queue.h k_message_queue.h k_tracebuffer.h k_itable.c k_utility.h k_scheduler.h api.h k_system_proc.h k_i_proc.h user_proc.h k_init_struct.h k_init.h k_globals.h k_defines.h 
TEST_SOURCES = test_queue.h test_priority_queue.h test_message_queue.h test_tracebuffer.h

# TODO Figure out proper way of linking using o files in obj/
OBJECTS_INTER = $(SOURCES:.h=.o)
OBJECTS = $(OBJECTS_INTER:.c=.o)
OBJECTS_DIR = $(OBJECTS:%=$(OBJ_DIR)%) 
TEST_OBJECTS_INTER = $(OBJECTS) $(TEST_SOURCES:.h=.o)
TEST_OBJECTS = $(TEST_OBJECTS_INTER:.c=.o)
TEST_OBJECTS_DIR = $(TEST_OBJECTS:%=$(OBJ_DIR)%)
OBJ_DIR = obj/

VPATH = inc:kern:test:kern/struct:init:proc:proc/inc:obj

MAIN = main.c
TEST_Q_MAIN = test/main_queue.c
TEST_PQ_MAIN = test/main_priority_queue.c
TEST_MQ_MAIN = test/main_message_queue.c
TEST_TB_MAIN = test/main_tracebuffer.c 
TEST_ITABLE_MAIN = test/main_itable.c 
TEST_UTILITY_MAIN = test/main_utility.c
TEST_SCHEDULER_MAIN = test/main_scheduler.c
TEST_KBD_MAIN = test/main_kbd.c
TEST_CRT_MAIN = test/main_crt.c


EXE = RTX 
TEST_Q_EXE = TEST_Q
TEST_PQ_EXE = TEST_PQ 
TEST_MQ_EXE = TEST_MQ
TEST_TB_EXE = TEST_TB
TEST_ITABLE_EXE = TEST_ITABLE
TEST_UTILITY_EXE = TEST_UTILITY
TEST_SCHEDULER_EXE = TEST_SCHEDULER
TEST_KBD_EXE = TEST_KBD
TEST_CRT_EXE = TEST_CRT

ALL_EXECUTABLE = $(EXE) $(TEST_Q_EXE) $(TEST_PQ_EXE) $(TEST_MQ_EXE) $(TEST_TB_EXE) $(TEST_ITABLE_EXE) $(TEST_UTILITY_EXE) $(TEST_SCHEDULER_EXE) $(TEST_KBD_EXE) $(TEST_CRT_EXE)

all: $(ALL_EXECUTABLE)

$(EXE): $(OBJECTS) $(MAIN)
	$(CC) $(LDFLAGS) $(OBJECTS_DIR) $(MAIN) -o $@
$(TEST_Q_EXE): $(TEST_OBJECTS) $(TEST_Q_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_Q_MAIN) -o $@
$(TEST_PQ_EXE): $(TEST_OBJECTS) $(TEST_PQ_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_PQ_MAIN) -o $@
$(TEST_MQ_EXE): $(TEST_OBJECTS) $(TEST_MQ_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_MQ_MAIN) -o $@
$(TEST_TB_EXE): $(TEST_OBJECTS) $(TEST_TB_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_TB_MAIN) -o $@
$(TEST_ITABLE_EXE): $(TEST_OBJECTS) $(TEST_ITABLE_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_ITABLE_MAIN) -o $@
$(TEST_UTILITY_EXE): $(TEST_OBJECTS) $(TEST_UTILITY_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_UTILITY_MAIN) -o $@
$(TEST_SCHEDULER_EXE): $(TEST_OBJECTS) $(TEST_SCHEDULER_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_SCHEDULER_MAIN) -o $@
$(TEST_KBD_EXE): $(TEST_OBJECTS) $(TEST_KBD_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_KBD_MAIN) -o $@
$(TEST_CRT_EXE): $(TEST_OBJECTS) $(TEST_CRT_MAIN)
	$(CC) $(LDFLAGS) $(TEST_OBJECTS_DIR) $(TEST_CRT_MAIN) -o $@


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
k_tracebuffer.o: k_tracebuffer.h k_defines.h
k_itable.o: 
k_io_buffer.o: k_io_buffer.c

k_scheduler: k_scheduler.h k_pcb.h k_queue.h k_priority_queue.h k_globals.h
k_utility.o: k_utility.h k_pcb.h k_queue.h k_defines.h k_globals.h

api.o: api.h k_pcb.h k_message.h k_queue.h k_priority_queue.h k_scheduler.h k_message.h k_message_queue.h k_tracebuffer.h  

k_system_proc.o: k_system_proc.h k_pcb.h k_message.h k_queue.h k_priority_queue.h k_scheduler.h k_message.h k_message_queue.h k_tracebuffer.h api.h 
k_system_proc.o: k_i_proc.h k_pcb.h k_message.h k_queue.h k_priority_queue.h k_scheduler.h k_message.h k_message_queue.h k_tracebuffer.h api.h 
user_proc.o: user_proc.h api.h

k_init_struct.o: k_init_struct.h k_pcb.h k_message.h k_queue.h k_priority_queue.h k_message_queue.h k_tracebuffer.h k_itable.c
k_init.o: k_init.h k_pcb.h k_message.h k_queue.h k_priority_queue.h k_message_queue.h k_tracebuffer.h k_itable.c k_init_struct.h k_system_proc.h k_defines.h k_globals.h

k_globals.o: k_globals.h k_pcb.h k_message.h k_queue.h k_priority_queue.h k_message_queue.h k_tracebuffer.h k_init_struct.h
k_defines.o: k_defines.h 
	
test_queue.o: k_queue.h k_pcb.h k_init_struct.h
test_priority_queue.o: test_priority_queue.h k_priority_queue.h k_init_struct.h
test_message_queue.o: test_message_queue.h k_message_queue.h k_init_struct.h
test_tracebuffer.o: test_tracebuffer.h k_tracebuffer.h k_init_struct.h
test_scheduler.o: test_scheduler.h k_scheduler.h k_pcb.h k_queue.h k_priority_queue.h
test_utility.o: test_utility.h k_pcb.h k_queue.h k_defines.h k_globals.h
kbd_helper.o: kbd_helper.c io_buffer.c
#crt_helper.o: crt_helper.c io_buffer.c

.PHONY: clean

clean:
	rm -f *.o $(ALL_EXECUTABLE)
	rm -rf $(OBJ_DIR)
