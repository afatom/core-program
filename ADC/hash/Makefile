#Project Files
TARGET=hashTest.out
OBJ=gdlist.o hashTest.o hash.o 

#Compilation Flags
cc=gcc
INC_PATH=../../include/
CFLAGS=-g -Wall -Werror -Wconversion -pedantic -ansi -I $(INC_PATH)
LDFLAGS=

#listTest dependencies
#First Rule: The Most Important One!

#ignore files with this names in our HDD
.PHONY:clean run gdb

$(TARGET): $(OBJ)
	$(cc) $(OBJ) -o $(TARGET) -lm

clean:
	rm -f $(OBJ) $(TARGET)
	@echo "ALL IS CLEAN"

run: $(TARGET)
	./$(TARGET)

gdb: $(TARGET)
	./$(TARGET)
	gdb ./$(TARGET)


#Object files dependencies
hash.o: $(INC_PATH)gdlist.h  $(INC_PATH)list_itr.h  $(INC_PATH)HashMap.h  $(INC_PATH)list_functions.h
hashTest.out:  $(INC_PATH)mu_test.h  $(INC_PATH)gdlist.h  $(INC_PATH)list_itr.h  $(INC_PATH)HashMap.h  $(INC_PATH)list_functions.h
gdlist.o: $(INC_PATH)gdlist.h  $(INC_PATH)list_itr.h  $(INC_PATH)list_functions.h
