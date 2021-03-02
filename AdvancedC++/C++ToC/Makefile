#Project Files
TARGET=exTest.out
OBJ=ex2.o

#Compilation Flags
cc=gcc
CFLAGS=-g -Wall -Werror -Wconversion -pedantic -ansi
LDFLAGS=

#vectorTest dependencies
#First Rule: The Most Important One!

#ignore files with this names in our HDD
.PHONY:clean run gdb	

$(TARGET): $(OBJ)
	$(cc) $(OBJ) -o $(TARGET) 

clean:
	rm -f $(OBJ)
	@echo "ALL IS CLEAN"

run: $(TARGET)
	clear
	./$(TARGET)

gdb: $(TARGET)
	./$(TARGET)
	gdb ./$(TARGET)
 	

#Object files dependencies
ex2.o: 
