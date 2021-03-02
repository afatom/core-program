# Project files
TARGET = heartsRun.out
OBJS = hearts.o deck.o game.o round.o trick.o player.o hand.o vector.o

TARGET_DECK = testDeck.out
OBJS_DECK = vector.o testDeck.o deck.o

TARGET_HAND = testHand.out
OBJS_HAND = vector.o testHand.o hand.o

# Compilation definitions

# Compiler:
CC = gcc
# Compilation flags:
CFLAGS =  -Wall -Werror -pedantic -Werror -g
# Linking flags:
LDFLAGS = -lm

.PHONY: clean run gdb

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(TARGET)
	
$(TARGET_HAND): $(OBJS_HAND)
	$(CC) $(OBJS_HAND) $(CFLAGS) -o $(TARGET_HAND)
	
$(TARGET_DECK): $(OBJS_DECK)
	$(CC) $(OBJS_DECK) $(CFLAGS) -o $(TARGET_DECK)

clean:
	rm -f $(OBJS_DECK) $(TARGET_DECK)
	rm -f $(OBJS_HAND) $(TARGET_HAND)
	@echo "All is clean" #the @ tells him to avoid writing the command, only the result will be printed
	
run: $(TARGET)
	 @clear
	 ./$(TARGET)

gdb: $(TARGET)
	 gdb ./$(TARGET)

test: hand_test deck_test

deck_test: $(TARGET_DECK)
		   @clear
		   ./$(TARGET_DECK)
	
hand_test: $(TARGET_HAND)
		   @clear
		   ./$(TARGET_HAND)


# Object files dependencies
vector.o : vector.h  ADTDefs.h  mu_test.h

deck.o: deck.h  vector.h  ADTDefs.h

deckTest: deck.h  mu_test.h

hand.o: vector.h  table.h  deck.h

handTest.o: hand.h  mu_test.h
