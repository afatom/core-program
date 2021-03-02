#Project Files
TARGET=memManTest.out
OBJ=memManager_t.o memPage_tTest.o memPage_t.o memPool_t.o 
SRCS=$(wildcard ./memManager_t.cpp ./memPage_t.cpp ./memPage_tTest.cpp ./memPool_t.cpp) 
OBJS=$(SRCS:.cpp=.o)
#Compilation Flags


INC_PATH=../include


CC=g++

CXXFLAGS=-g -Wall -Werror -Wconversion -pedantic -ansi -I$(INC_PATH)
LDFLAGS=

.PHONY: clean run gdb

$(TARGET): depends $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) 

clean:
	rm -f $(OBJS) $(TARGET) depends *.out *.o
	@clear

run: $(TARGET)
	@clear
	./$(TARGET)
	
gdb: $(TARGET)
	gdb ./$(TARGET) -q

depends:
	$(CC) -MM $(SRCS) > depends

include depends   

