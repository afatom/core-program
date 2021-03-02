#Project Files
TARGET=channelTest.out
OBJ=channel.o channelTest.o 

#Compilation Flags
cc=gcc
INC_PATH= ../../include/
CFLAGS=-g -Wall -Werror -Wconversion -pedantic -ansi -I $(INC_PATH)
LDFLAGS= -_GNU_SOURCE


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
channel.o: $(INC_PATH)channel.h
channelTest.o: $(INC_PATH)channel.h  $(INC_PATH)mu_test.h

