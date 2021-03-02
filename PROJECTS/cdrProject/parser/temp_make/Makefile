#Project Files
TARGET=parserTest.out
OBJ=parser.o parserTest.o cdr.o channel.o

#Compilation Flags
#-Wall -Werror -Wconversion
cc=gcc
INC_PATH=../../../include/
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
parser.o: $(INC_PATH)parser.h 
#parserTest.out: $(INC_PATH)parser.h
parserTest.o: $(INC_PATH)parser.h
cdr.o:
channel.o:
