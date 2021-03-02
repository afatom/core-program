#Project Files
TARGET=channelTest.out
OBJ=channel.o channelTest.o 

#Compilation Flags
cc=gcc
CFLAGS=-g -Wall -Werror -Wconversion -pedantic 
LDFLAGS= 
#-_GNU_SOURCE

#vectorTest dependencies
#First Rule: The Most Important One!

#ignore files with this names in our HDD
.PHONY:clean run gdb	

$(TARGET): $(OBJ)
	$(cc) $(OBJ) -o $(TARGET) -pthread -lpthread -lrt  

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
channel.o: channel.h 
channelTest.o: channel.h mu_test.h

