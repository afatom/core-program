#Project Files
TARGET=vectorTest.out
OBJ=vector.o vectorTest.o

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
vector.o: $(INC_PATH)vector.h
vectorTest.out: $(INC_PATH)vector.h $(INC_PATH)mu_test.h 



