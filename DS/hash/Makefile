#Project Files
TARGET=hashTest.out
OBJ=hash.o hashTest.o

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
list.o: hash.h ADTDefs.h
listTest.out: ADTDefs.h hash.h mu_test.h
