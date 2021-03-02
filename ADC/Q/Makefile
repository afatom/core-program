#Project Files
TARGET=queueTest.out
OBJ=queue.o queueTest.o gdlist.o 

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
queue.o: $(INC_PATH)queue.h $(INC_PATH)gdlist.h $(INC_PATH)list_functions.h $(INC_PATH)list_itr.h
queueTest.out: $(INC_PATH)queue.h $(INC_PATH)mu_test.h 
gdlist.o: $(INC_PATH)gdlist.h $(INC_PATH)list_functions.h $(INC_PATH)list_itr.h
