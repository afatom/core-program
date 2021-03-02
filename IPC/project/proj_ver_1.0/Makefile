#Project Files
TARGET=aggTest.out
OBJ=gdlist.o aggregator.o hash.o cdr.o aggTest.o

#Compilation Flags
cc=gcc
INC_PATH=../../../include/
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
hash.o: $(INC_PATH)gdlist.h $(INC_PATH)list_itr.h $(INC_PATH)HashMap.h $(INC_PATH)list_functions.h
#aggTest.out:  $(INC_PATH)mu_test.h $(INC_PATH)HashMap.h $(INC_PATH)aggregator.h $(INC_PATH)cdr.h
aggTest.o: $(INC_PATH)mu_test.h $(INC_PATH)HashMap.h $(INC_PATH)aggregator.h $(INC_PATH)cdr.h
gdlist.o: $(INC_PATH)gdlist.h  $(INC_PATH)list_itr.h  $(INC_PATH)list_functions.h
aggregator.o: $(INC_PATH)HashMap.h $(INC_PATH)aggregator.h $(INC_PATH)cdr.h
cdr.o: $(INC_PATH)cdr.h




