#Project Files
TARGET=recTest.out
OBJ=rec.o recTest.o

#Compilation Flags
cc=gcc
#-g -Wall -Werror -Wconversion -pedantic -ansi
CFLAGS=-g -pedantic -ansi -Wconversion
LDFLAGS=

#recursionTest dependencies
#First Rule: The Most Important One!

#ignore files with this names in our HDD
.PHONY:clean run gdb

$(TARGET): $(OBJ)
	$(cc) $(OBJ) -o $(TARGET)   #like: gcc rec.o recTest.o -o recTest

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
rec.o: recursion.h
recTest.o: recursion.h mu_test.h
