#Project Files
TARGET=eventtest.out
OBJ=eventtest.o nevent.o 
SRCS=$(wildcard ./eventtest.cpp ./nevent.cpp) 
OBJS=$(SRCS:.cpp=.o)
#Compilation Flags


INC_PATH=../include


CC=g++
# -Wconversion  -Wall 
CXXFLAGS=-g -Werror -pedantic -ansi -Wconversion -I$(INC_PATH)
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

