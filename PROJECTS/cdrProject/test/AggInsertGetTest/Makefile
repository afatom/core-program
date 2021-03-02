# Project files
TARGET=aggGetTest.out
SRCS=$(wildcard ./*.c ../../aggregator/aggregatorVer2.c ../../cdrReader/cdr.c ../../dataBase/*.c ../../../../ADC/hash/hash.c ../../../../ADC/hash/gdlist.c)
OBJS=$(SRCS:.c=.o)
#OBJS=aggTest.o aggregator.o cdr.o #all unsafe hash files


#TARGET_VER_1=cdrProjectVer1.out
#SRCS_VER_1=$(wildcard ../cdrProject/aggregator/*.c ../cdrProject/cdrReader/*.c ../cdrProject/test/*.c ../../ADC/hash/hash.c ../../ADC/hash/gdlist.c)
#OBJS_VER_1=$(SRCS:.c=.o)


# Compilation definitions

INC_PATH=$(addprefix -I, ../../../../include)

# Compiler:
CC=gcc
# Compilation flags: -Wall -Werror 
CFLAGS=-g -Wconversion -pedantic -ansi -std=c99 $(INC_PATH)
# Linking flags:
LDFLAGS= 

.PHONY: clean run gdb

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) -lm -pthread
	
clean:
	rm -f $(OBJS) $(TARGET)
	@clear
	
cls:
	ipcrm --all=msg
	ipcs
	clear
	
clear:
	ipcrm --all=msg
	ipcs
	clear


run: $(TARGET)
	@clear
	./$(TARGET)

gdb: $(TARGET)
	gdb ./$(TARGET)

# Object files dependencies

