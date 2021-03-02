#Project Files
TARGET=stackTest.out
OBJ=stack.o vector.o stackTest.o

#Compilation Flags
cc=gcc
CFLAGS=-g -Wall -Werror -Wconversion -pedantic -ansi
LDFLAGS=

#vectorTest dependencies
#First Rule: The Most Important One!

#ignore files with this names in our HDD
.PHONY:clean run gdb

$(TARGET): $(OBJ)
	$(cc) $(OBJ) -o $(TARGET)   #like: gcc vector.o vectorTest.o -o vectorTest

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
vector.o: vector.h ADTDefs.h stack.h
vectorTest.o: vector.h ADTDefs.h mu_test.h stack.h
