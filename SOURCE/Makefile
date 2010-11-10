CC = gcc
CFLAGS = -Wall -g  -I./$(INC_DIR) 
LDFLAGS = -g -I./$(INC_DIR) 

INC_DIR = inc/

SOURCES = pcb.h message.h queue.h priority_queue.h message_queue.h tracebuffer.h globals.h defines.h 
TEST_SOURCES = test_queue.h test_priority_queue.h test_message_queue.h test_tracebuffer.h

# TODO Figure out proper way of linking using o files in obj/
OBJECTS = $(SOURCES:.h=.o)
OBJECTS_DIR = $(OBJECTS:%=$(OBJ_DIR)%) 
TEST_OBJECTS = $(OBJECTS) $(TEST_SOURCES:.h=.o)
TEST_OBJECTS_DIR = $(TEST_OBJECTS:%=$(OBJ_DIR)%)
OBJ_DIR = obj/

MAIN = main.c
TEST_Q_MAIN = test/main_queue.c
TEST_PQ_MAIN = test/main_priority_queue.c
TEST_MQ_MAIN = test/main_message_queue.c
TEST_TB_MAIN = test/main_tracebuffer.c 

VPATH = inc:kern:test:kern/struct:obj

EXE = RTX 
TEST_Q_EXE = TEST_Q
TEST_PQ_EXE = TEST_PQ 
TEST_MQ_EXE = TEST_MQ
TEST_TB_EXE = TEST_TB

ALL_EXECUTABLE = $(EXE) $(TEST_Q_EXE) $(TEST_PQ_EXE) $(TEST_MQ_EXE) $(TEST_TB_EXE)

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

$(OBJECTS): | $(OBJ_DIR)
$(TEST_OBJECTS): | $(OBJ_DIR)

$(OBJ_DIR):
	@echo $(OBJECTS) 
	mkdir $(OBJ_DIR)
.c.o:
	$(CC) $(CFLAGS) -c -o $(OBJ_DIR)$@ $<

pcb.o: pcb.h
message.o: message.h defines.h

queue.o: queue.h pcb.h
priority_queue.o : queue.h pcb.h
message_queue.o: message_queue.h message.h
tracebuffer.o: tracebuffer.h

globals.o: globals.h pcb.h message.h queue.h priority_queue.h message_queue.h
defines.o: defines.h 

test_queue.o: queue.h pcb.h
test_priority_queue.o: test_priority_queue.h priority_queue.h
test_message_queue.o: test_message_queue.h message_queue.h
test_tracebuffer.o: test_tracebuffer.h tracebuffer.h

.PHONY: clean

clean:
	rm -f *.o $(ALL_EXECUTABLE)
	rm -rf $(OBJ_DIR)
