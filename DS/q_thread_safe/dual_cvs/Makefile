#Project Files
TARGET=queueTest.out
OBJ=queue.o queueTest.o gdlist.o 

#Compilation Flags
#-Wall -Werror -Wconversion
cc=gcc
#INC_PATH=../../include/
#-I $(INC_PATH)
CFLAGS=-g -pedantic -ansi -Wconversion -Wall -Werror 
# Linker flags:
LDFLAGS=

#listTest dependencies
#First Rule: The Most Important One!

#ignore files with this names in our HDD
.PHONY:clean run gdb

$(TARGET): $(OBJ)
	$(cc) $(OBJ) -o $(TARGET) -pthread

clean:
	rm -f $(OBJ) $(TARGET)
	@echo "CLEAN !"

run: $(TARGET)
	./$(TARGET)


gdb: $(TARGET)
	./$(TARGET)
	gdb ./$(TARGET)


#Object files dependencies
queue.o: tsqueue.h gdlist.h list_functions.h list_itr.h
queueTest.out: tsqueue.h mu_test.h 
gdlist.o: gdlist.h list_functions.h list_itr.h
