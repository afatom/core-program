#Project Files
TARGET=carTest.out
OBJ=car_t.o appTest.o bus_t.o private_t.o
SRCS=$(wildcard ./car_t.cpp ./bus_t.cpp ./private_t.cpp ./appTest.cpp) 
OBJS=$(SRCS:.cpp=.o)
#Compilation Flags


INC_PATH=../../include


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

