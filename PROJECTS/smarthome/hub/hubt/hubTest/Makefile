#Project Files


TARGET=hubTest.out
OBJ=hubTest.o nevent.o distributor.o publisher.o registrar.o hub.o agentconfig.o lgsensor.o lgcontroler.o
SRCS=$(wildcard ./hubTest.cpp ../hub.cpp ../../../event/nevent.cpp ../../../setup/fileConfig/agentconfig.cpp ./lgcontroler.cpp ./lgsensor.cpp ../../publisher/publisher.cpp ../../distributor/distributor.cpp ../../registrar/registrar.cpp) 

OBJS=$(SRCS:.cpp=.o)
#Compilation Flags


INC_PATH=../../../include


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

