#Project Files
TARGET=gsortTest.out
OBJ=gsort.o gsortTest.o

#Compilation Flags
cc=gcc
CFLAGS=-g -Wall -Werror -Wconversion -pedantic -ansi
LDFLAGS=

#vectorTest dependencies
#First Rule: The Most Important One!

#ignore files with this names in our HDD
.PHONY:clean run gdb

$(TARGET): $(OBJ)
	$(cc) $(OBJ) $(CFLAGS) -o $(TARGET)

clean:
	rm -f $(OBJ)
	@echo "ALL IS CLEAN"

gsortTest: $(TARGET)
	./$(TARGET)

gdb: $(TARGET)
	./$(TARGET)
	gdb ./$(TARGET)


#Object files dependencies
gsortTest.o: gsort.h ADTDefs.h mu_test.h
gsort.o: gsort.h ADTDefs.h
