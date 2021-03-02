#Project Files
TARGET=barrierTest.out
OBJ=barrier.o barrierTest.o 

#Compilation Flags
#-Wall -Werror -Wconversion
cc=gcc
#INC_PATH=../../include/
#-I $(INC_PATH)
CFLAGS=-g -pedantic -Wconversion -Wall -Werror 
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
barrier.o: barrier.h 
barrierTest.out: mu_test.h barrier.h 
