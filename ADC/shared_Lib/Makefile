#Project Files
TARGET=sharedLib.out
OBJ=sharedLib.o

#Compilation Flags
# -Werror
cc=gcc
INC_PATH=../../include/
CFLAGS=-g -pedantic -ansi -Wconversion -Wall -I $(INC_PATH)
# Linker flags:
LDFLAGS=-rdynamic -ldl

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
sharedLib.o: $(INC_PATH)vector.h $(INC_PATH)mu_test.h 
sharedLib.out: $(INC_PATH)vector.h $(INC_PATH)mu_test.h 
