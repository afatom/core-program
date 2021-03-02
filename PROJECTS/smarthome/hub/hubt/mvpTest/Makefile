#Project Files

TARGET=mvpTest.out
OBJ=mvpTest.o nevent.o distributor.o publisher.o registrar.o hub.o 
SRCS=$(wildcard ../hup.cpp ./mvpTest.cpp ../../../event/nevent.cpp ../../publisher/publisher.cpp ../../distributor/distributor.cpp ../../registrar/registrar.cpp) 


#TARGET=hubshpTest.out
#OBJ=hubshpTest.o nevent.o distributor.o publisher.o registrar.o hub.o 
#SRCS=$(wildcard ./hubshpTest.cpp ../../event/nevent.cpp ../publisher/publisher.cpp ../distributor/distributor.cpp ../registrar/registrar.cpp) 

OBJS=$(SRCS:.cpp=.o)
#Compilation Flags


INC_PATH= ../../../include


CC=g++
# -Wconversion  -Wall 
CXXFLAGS=-g -Werror -pedantic -ansi -Wconversion -I$(INC_PATH)
LDFLAGS=

.PHONY: clean run gdb

$(TARGET): depends $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) -pthread

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

