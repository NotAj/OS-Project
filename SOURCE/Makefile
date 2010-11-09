CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -g
SOURCES = pcb.h queue.h priority_queue.h 
TEST_SOURCES = test_queue.h test_priority_queue.h
OBJECTS = $(SOURCES:.h=.o) $(TEST_SOURCES:.h=.o)

MAIN = main.c
EXECUTABLE = test

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(MAIN)
	$(CC) $(LDFLAGS) $(OBJECTS) $(MAIN) -o $@

pcb.o: pcb.h

queue.o test_queue.o priority_queue.o : queue.h pcb.h

test_priority_queue.o: test_priority_queue.h

clean:
	rm -f *.o $(EXECUTABLE)
