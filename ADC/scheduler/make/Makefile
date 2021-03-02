#Project Files

TARGET = managerTest.out 
OBJS = task.o scheduler.o heap.o vector.o managerTest.o time.o zlog4c.o manager.o

TARGET_SCHEDULER = schedulerTest.out
OBJS_SCHEDULER = scheduler.o heap.o vector.o schedulerTest.o task.o time.o zlog4c.o

#TARGET_TASK = taskTest.out
#OBJS_TASK = task.o taskTest.o

#TARGET_TIME = timeTest.out
#OBJS_TIME = time.o timeTest.o

#Compilation Flags
#-Wall -Werror -Wconversion
cc=gcc
INC_PATH=../../include/
CFLAGS=-g -pedantic -ansi -Wconversion -Wall -Werror -I $(INC_PATH) 
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
scheduler.o:$(INC_PATH)heap.h $(INC_PATH)scheduler.h $(INC_PATH)vector.h $(INC_PATH)ttime.h $(INC_PATH)task.h $(INC_PATH)zlog4c.h 
schedulerTest.out: $(INC_PATH)heap.h $(INC_PATH)mu_test.h $(INC_PATH)vector.h $(INC_PATH)scheduler.h $(INC_PATH)ttime.h $(INC_PATH)task.h 
heap.o: $(INC_PATH)heap.h $(INC_PATH)vector.h
vector.o: $(INC_PATH)vector.h
task.o: $(INC_PATH)task.h 
taskTest.o:$(INC_PATH)task.h $(INC_PATH)mu_test.h
time.o:$(INC_PATH)ttime.h
timeTest.o:$(INC_PATH)ttime.h $(INC_PATH)mu_test.h
manager.o:$(INC_PATH)task.h $(INC_PATH)scheduler.h $(INC_PATH)task.h $(INC_PATH)manager.h
managerTest.out:$(INC_PATH)heap.h $(INC_PATH)scheduler.h $(INC_PATH)vector.h $(INC_PATH)ttime.h $(INC_PATH)task.h $(INC_PATH)zlog4c.h $(INC_PATH)mu_test.h $(INC_PATH)manager.h











