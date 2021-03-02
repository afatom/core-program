# Projet files
TARGET2 = aggregator.out
OBJS2 =   aggregator.o channel.o

TARGET = reader.out
OBJS =   reader.o channel.o

# Compilation definitions

# Compiler:
CC = gcc
INC_PATH= ../../include/

# Compilation flags:
CFLAGS=-g -Wall -Werror -Wconversion -pedantic -ansi -I$(INC_PATH)
# Linking flags:
LDFLAGS = -lm -_GNU_SOURCE

.PHONY: clean run gdb

$(TARGET): $(OBJS)
	$(CC) -I$(INC_PATH) $(OBJS) -o $(TARGET) 

$(TARGET2): $(OBJS2)
	$(CC) -I$(INC_PATH) $(OBJS2) -o $(TARGET2) 


clean:
	rm -f $(OBJS) $(TARGET)
		
clean2:
	rm -f $(OBJS2) $(TARGET2)
	

run: $(TARGET)
	@clear
	./$(TARGET)

run2: $(TARGET2)
	@clear
	./$(TARGET2)
	
gdb1: $(TARGET)
	gdb ./$(TARGET)
		
gdb2: $(TARGET2)
	gdb ./$(TARGET2)
	
# Object files dependencies
channel.o: $(INC_PATH)/channel.h
reader.o: $(INC_PATH)/channel.h
aggregator.o: $(INC_PATH)/channel.h


