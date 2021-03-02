#Project Files
TARGET=heapTest.out
OBJ=heap.o heapTest.o vector.o

#Compilation Flags
#-Wall -Werror -Wconversion
cc=gcc
CFLAGS=-g -pedantic -ansi -Wconversion -Wall
LDFLAGS=

#listTest dependencies
#First Rule: The Most Important One!

#ignore files with this names in our HDD
.PHONY:clean run gdb

$(TARGET): $(OBJ)
	$(cc) $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ)
	@echo "ALL IS CLEAN"

run: $(TARGET)
	clear
	./$(TARGET)

gdb: $(TARGET)
	./$(TARGET)
	gdb ./$(TARGET)


#Object files dependencies
list.o: heap.h vector.h ADTDefs.h
listTest.out: ADTDefs.h heap.h mu_test.h vector.h
