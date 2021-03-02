#Project Files
TARGET=mallocTest.out
OBJ=mallocTest.o malloc.o 

#Compilation Flags
cc=gcc
INC_PATH=../../include/
CFLAGS=-g -pedantic -ansi -Wpadded -Wconversion -Wall -Werror -I $(INC_PATH)
# Linker flags:
LDFLAGS=


#ignore files with this names in our HDD
.PHONY:clean run gdb	

$(TARGET): $(OBJ)
	$(cc) $(OBJ) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
	@echo "ALL IS CLEAN"

run: $(TARGET)
	clear
	./$(TARGET)

gdb: $(TARGET)
	./$(TARGET)
	gdb ./$(TARGET)
 	

#Object files dependencies
mallocTest.o: $(INC_PATH)mmalloc.h $(INC_PATH)mu_test.h
malloc.o: $(INC_PATH)mmalloc.h 

