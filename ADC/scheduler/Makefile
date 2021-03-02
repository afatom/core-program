#Project Files

#TARGET = managerTest.out 
#OBJS = task.o scheduler.o heap.o vector.o managerTest.o time.o manager.o

TARGET = schedulerTest.out
OBJS = scheduler.o heap.o vector.o task.o time.o schedulerTest.o

#TARGET_TASK = taskTest.out
#OBJS_TASK = task.o taskTest.o

#TARGET_TIME = timeTest.out
#OBJS_TIME = time.o timeTest.o

#Compilation Flags
#-Wall -Werror -Wconversion
cc=gcc

CFLAGS=-g -pedantic -ansi -Wconversion -Wall -Werror
# Linker flags:
LDFLAGS=

#listTest dependencies
#First Rule: The Most Important One!

#ignore files with this names in our HDD
.PHONY:clean run gdb

$(TARGET): $(OBJS)
	$(cc) $(OBJS) $(CFLAGS) -o $(TARGET)

#$(TARGET_TASK): $(OBJS_TASK)
	#$(CC) $(OBJS_TASK) $(CFLAGS) -o $(TARGET_TASK)
	
#$(TARGET_TIME): $(OBJS_TIME)
	#$(CC) $(OBJS_TIME) $(CFLAGS) -o $(TARGET_TIME)

#clean scheduler:
#	rm -f $(OBJS_SCHEDULER) $(TARGET_SCHEDULER)
#	@echo "CLEAN !"

clean:
	rm -f $(OBJS) $(TARGET)
	@echo "CLEAN !"
	
#clean:
#	rm -f $(OBJS_TASK) $(TARGET_TASK)
#	@echo "CLEAN !"

#run task : $(TARGET_TASK)
#	./$(TARGET_TASK)

run : $(TARGET)
	./$(TARGET)
	
#run scheduler: $(TARGET_SCHEDULER)
#	./$(TARGET_SCHEDULER)

gdb: $(TARGET)
	./$(TARGET)
	gdb ./$(TARGET)


#Object files dependencies
scheduler.o:heap.h scheduler.h vector.h ttime.h task.h  
schedulerTest.out: heap.h mu_test.h vector.h scheduler.h ttime.h task.h 
heap.o: heap.h vector.h
vector.o: vector.h
task.o: task.h 
taskTest.o:task.h mu_test.h
time.o:ttime.h
timeTest.o:ttime.h mu_test.h
manager.o:task.h scheduler.h task.h manager.h
managerTest.out:heap.h scheduler.h vector.h ttime.h task.h  mu_test.h manager.h











