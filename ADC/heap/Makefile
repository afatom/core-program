#Project Files
TARGET=heapTest.out
OBJ=heap.o heapTest.o vector.o

#Compilation Flags
#-Wall -Werror -Wconversion
cc=gcc
INC_PATH=../../include/
CFLAGS=-g -pedantic -ansi -Wconversion -Wall -Werror -I $(INC_PATH)
# Linker flags:
LDFLAGS=

#listTest dependencies
#First Rule: The Most Important One!

#ignore files with this names in our HDD
.PHONY:clean run gdb

$(TARGET): $(OBJ)
	$(cc) $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
	@echo "CLEAN !"

run: $(TARGET)
	./$(TARGET)


gdb: $(TARGET)
	./$(TARGET)
	gdb ./$(TARGET)


#Object files dependencies
heap.o: $(INC_PATH)heap.h $(INC_PATH)vector.h
heapTest.out: $(INC_PATH)heap.h $(INC_PATH)mu_test.h $(INC_PATH)vector.h
vector.o: $(INC_PATH)mu_test.h $(INC_PATH)vector.h
