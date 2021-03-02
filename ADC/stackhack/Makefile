#Project Files
TARGET=hackthestack.out
OBJ=hackthestack.o

#Compilation Flags
#-Wall -Werror -Wconversion -pedantic -ansi
cc=gcc
CFLAGS=-g 
LDFLAGS=

#vectorTest dependencies
#First Rule: The Most Important One!

#ignore files with this names in our HDD
.PHONY:clean run gdb

$(TARGET): $(OBJ)
	$(cc) $(OBJ) $(CFLAGS) -o $(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
	@echo "ALL IS CLEAN"

gsortTest: $(TARGET)
	./$(TARGET)

gdb: $(TARGET)
	./$(TARGET)
	gdb ./$(TARGET)


#Object files dependencies

