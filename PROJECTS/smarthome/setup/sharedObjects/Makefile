#Project Files


##TARGET=SOLoadingTest.out
##OBJ=main.o nevent.o distributor.o publisher.o registrar.o hub.o agentconfig.o
##SRCS=$(wildcard ./main.cpp ../../fileConfig/agentconfig.cpp ../../../hub/hubt/hub.cpp ../../../../event/nevent.cpp ../../../hub/publisher/publisher.cpp ../../../hub/distributor/distributor.cpp ../../../hub/registrar/registrar.cpp) 

TARGET=SOLoadingTest.out
OBJ=main.o nevent.o distributor.o publisher.o registrar.o hub.o agentconfig.o
SRCS=$(wildcard ./main.cpp ../../fileConfig/agentconfig.cpp ../../../hub/hubt/hub.cpp ../../../../event/nevent.cpp ../../../hub/publisher/publisher.cpp ../../../hub/distributor/distributor.cpp ../../../hub/registrar/registrar.cpp) 


OBJS=$(SRCS:.cpp=.o)
#Compilation Flags


INC_PATH=../../include


CC=g++
# -Wconversion  -Wall 
CXXFLAGS=-fPIC -g -c -Werror -pedantic -ansi -Wconversion -I$(INC_PATH)
LDFLAGS=

.PHONY: clean run gdb

$(TARGET): depends $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) -pthread -ldl

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

