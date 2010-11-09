CC = gcc
CFLAGS = -Wall -g -I./inc/
LDFLAGS = -g -I./inc/

SOURCES = pcb.h message.h queue.h priority_queue.h message_queue.h globals.h defines.h test_queue.h test_priority_queue.h test_message_queue.h

OBJECTS = $(SOURCES:.h=.o) $(TEST_SOURCES:.h=.o)

MAIN = tests/main.c

VPATH = inc:tests:structs

EXECUTABLE = RTX 


all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(MAIN)
	$(CC) $(LDFLAGS) $(OBJECTS) $(MAIN) -o $@

pcb.o: pcb.h

queue.o test_queue.o priority_queue.o : queue.h pcb.h

test_priority_queue.o: test_priority_queue.h

message.o: message.h defines.h

globals.o: globals.h pcb.h message.h queue.h priority_queue.h message_queue.h

defines.o: defines.h 

message_queue.o : message_queue.h message.h

test_message_queue.o: test_message_queue.h

clean:
	rm -f *.o $(EXECUTABLE)
