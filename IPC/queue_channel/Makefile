# Projet files
TARGET=channel.out 
OBJS= channel.o reader_aggregator.o


# Compilation definitions

# Compiler:
CC=gcc
INC_PATH= ../queue_channel/
# Compilation flags:
CFLAGS=-g -Wall -Werror -Wconversion -pedantic -I $(INC_PATH)
# Linking flags:
LDFLAGS=

.PHONY: clean run gdb

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) -pthread -lpthread

clean: $(OBJS)
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	@clear
	./$(TARGET)

gdb: $(TARGET)
	gdb ./$(TARGET)

# Object files dependencies
channel.o:  $(INC_PATH)channel.h
reader_aggregator.o: $(INC_PATH)channel.h

