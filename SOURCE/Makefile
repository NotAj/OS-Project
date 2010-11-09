CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -g
SOURCES = pcb.h queue.h priority_queue.h message_queue.h 
TEST_SOURCES = test_queue.h test_priority_queue.h test_message_queue.h
OBJECTS = $(SOURCES:.h=.o) $(TEST_SOURCES:.h=.o)

MAIN = main.c
EXECUTABLE = test

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(MAIN)
	$(CC) $(LDFLAGS) $(OBJECTS) $(MAIN) -o $@

pcb.o: pcb.h

queue.o test_queue.o priority_queue.o : queue.h pcb.h

test_priority_queue.o: test_priority_queue.h

message.o: message.h defines.h

globals.h: pcb.h message.h queue.h priority_queue.h message_queue.h

message_queue.o : message_queue.h message.h

test_message_queue.o: test_message_queue.h


clean:
	rm -f *.o $(EXECUTABLE)
