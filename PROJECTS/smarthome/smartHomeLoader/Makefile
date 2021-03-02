#Project Files
TARGET=smartHome.out
OBJ= smartHomeMain.o smartHome.o registrar.o nevent.o publisher.o agentconfig.o txtreader.o agentsBuilder.o setup.o distributor.o hub.o agentsFactory.o soloader.o
SRCS=$(wildcard ./smartHomeMain.cpp ../setup/fileConfig/agentconfig.cpp ../setup/fileConfig/txtreader.cpp ../setup/SOLoader/soloader.cpp ../setup/agentsFactory/agentsFactory.cpp ../setup/agentsFactory/agentsBuilder.cpp ../setup/setup.cpp ../event/nevent.cpp ./smartHome.cpp ../hub/registrar/registrar.cpp ../hub/distributor/distributor.cpp ../hub/publisher/publisher.cpp ../hub/hubt/hub.cpp)
OBJS=$(SRCS:.cpp=.o)
#Compilation Flags


INC_PATH= ../include


CC=g++
# -Wconversion  -Wall 
CXXFLAGS=-g -Werror -pedantic -ansi -Wconversion -I$(INC_PATH)
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

