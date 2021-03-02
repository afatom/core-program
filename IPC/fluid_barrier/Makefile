#Project Files
TARGET=barrierTest.out
OBJ=barrier.o main.o 

#Compilation Flags
cc=gcc
INC_PATH=../../include/
CFLAGS=-g -pedantic -ansi -Wpadded -Wconversion -Wall -Werror -I $(INC_PATH)
# Linker flags:
LDFLAGS=


#listTest dependencies
#First Rule: The Most Important One!

#ignore files with this names in our HDD
.PHONY:clean run gdb

$(TARGET): $(OBJ)
	$(cc) $(OBJ) -o $(TARGET) -pthread -lpthread

clean:
	rm -f $(OBJ) $(TARGET)
	@echo "CLEAN !"

run: $(TARGET)
	./$(TARGET)


gdb: $(TARGET)
	./$(TARGET)
	gdb ./$(TARGET)


#Object files dependencies
barrier.o: $(INC_PATH)FluidBarrier.h 
main.o:  $(INC_PATH)FluidBarrier.h $(INC_PATH)mu_test.h
