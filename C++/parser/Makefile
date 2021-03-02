#Project Files
TARGET=main.out
OBJ=main.o analyzer_t.o parser_t.o tokenizer_t.o
SRCS=$(wildcard ./main.cpp ./analyzer_t.cpp ./parser_t.cpp ./tokenizer_t.cpp) 
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

