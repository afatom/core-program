#Project Files
TARGET=shpointer.out
SRCS=$(wildcard ./shptr.cpp) 
OBJS=$(SRCS:.cpp=.o)


#Compilation Flags

INC_PATH=$(addprefix -I, ./)

CC=g++

CXXFLAGS=-g -Wall -ansi -pedantic -Werror -Wconversion -std=c++11 $(INC_PATH) 

LDFLAGS= 
.PHONY: clean run gdb

$(TARGET): depends $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
	
clean:
	rm -f $(OBJS) $(TARGET) *.out *.o *.so depends
	@clear

run: $(TARGET)
	@clear
	./$(TARGET) 
	
gdb: $(TARGET)
	gdb ./$(TARGET)

depends:
	$(CC) -MM $(SRCS) $(INC_PATH) > depends
	
#include depends   
#g++ -fPIC -shared LG_fire_sens_1.h -o LG_fire_sens_1.so -I../include

