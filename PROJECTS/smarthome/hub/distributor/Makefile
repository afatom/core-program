#Project Files
TARGET=distributorTest.out
OBJ=distributorTest.o distributor.o nevent.o registrar.o
SRCS=$(wildcard ./distributorTest.cpp ./distributor.cpp ../../event/nevent.cpp ../registrar/registrar.cpp) 
OBJS=$(SRCS:.cpp=.o)
#Compilation Flags


INC_PATH=../../include


CC=g++
# -Wconversion  -Wall 
CXXFLAGS=-g -Werror -pedantic -ansi -Wconversion -I$(INC_PATH)
LDFLAGS=

.PHONY: clean run gdb

$(TARGET): depends $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) -pthread -lpthread

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

