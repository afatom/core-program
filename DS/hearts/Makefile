# Project files
TARGET = game.out
OBJS = round.o player.o trick.o vector.o deck.o vectorsort.o hand.o game.o main.o ui.o

TARGET_DECK = deckTest.out
OBJS_DECK = vector.o deckTest.o deck.o ui.o

TARGET_HAND = handTest.out
OBJS_HAND = vector.o handTest.o hand.o vectorsort.o deck.o ui.o

TARGET_PLAYER = playerTest.out
OBJS_PLAYER = vector.o playerTest.o hand.o vectorsort.o deck.o player.o ui.o

TARGET_TRICK = trickTest.out
OBJS_TRICK = vector.o trickTest.o hand.o vectorsort.o deck.o player.o trick.o ui.o

TARGET_ROUND = roundTest.out
OBJS_ROUND = round.o roundTest.o player.o trick.o vector.o deck.o vectorsort.o hand.o ui.o

TARGET_GAME = gameTest.out
OBJS_GAME = round.o player.o trick.o vector.o deck.o vectorsort.o hand.o game.o gameTest.o ui.o

# Compilation definitions

# Compiler:
CC = gcc
# Compilation flags:
CFLAGS =  -Wall -Werror -pedantic -ansi -g
# Linking flags:
LDFLAGS = -lm

.PHONY: clean run gdb

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(TARGET)

$(TARGET_HAND): $(OBJS_HAND)
	$(CC) $(OBJS_HAND) $(CFLAGS) -o $(TARGET_HAND)

$(TARGET_DECK): $(OBJS_DECK)
	$(CC) $(OBJS_DECK) $(CFLAGS) -o $(TARGET_DECK)

$(TARGET_PLAYER): $(OBJS_PLAYER)
	$(CC) $(OBJS_PLAYER) $(CFLAGS) -o $(TARGET_PLAYER)

$(TARGET_TRICK): $(OBJS_TRICK)
	$(CC) $(OBJS_TRICK) $(CFLAGS) -o $(TARGET_TRICK)

$(TARGET_ROUND): $(OBJS_ROUND)
	$(CC) $(OBJS_ROUND) $(CFLAGS) -o $(TARGET_ROUND)

$(TARGET_GAME): $(OBJS_GAME)
	$(CC) $(OBJS_GAME) $(CFLAGS) -o $(TARGET_GAME)



clean:
	rm -f $(OBJS_DECK) $(TARGET_DECK)
	rm -f $(OBJS_HAND) $(TARGET_HAND)
	rm -f $(OBJS_PLAYER) $(TARGET_PLAYER)
	rm -f $(OBJS_TRICK) $(TARGET_TRICK)
	rm -f $(OBJS_ROUND) $(TARGET_ROUND)
	rm -f $(OBJS_GAME) $(TARGET_GAME)

	@echo "All is clean" #the @ tells him to avoid writing the command, only the result will be printed

run: $(TARGET)
	 @clear
	 ./$(TARGET)

gdb: $(TARGET)
	 gdb ./$(TARGET)

test: hand_test deck_test player_test trick_test round_test

deck_test: $(TARGET_DECK)

		   ./$(TARGET_DECK)

hand_test: $(TARGET_HAND)

		   ./$(TARGET_HAND)

player_test: $(TARGET_PLAYER)

		   ./$(TARGET_PLAYER)

trick_test: $(TARGET_TRICK)

		   ./$(TARGET_TRICK)

round_test: $(TARGET_ROUND)

		   ./$(TARGET_ROUND)

game_test: $(TARGET_GAME)

		   ./$(TARGET_GAME)

# Object files dependencies
vector.o : vector.h  ADTDefs.h  mu_test.h

vectorsort.o : vector.h  ADTDefs.h  mu_test.h vectorsort.h ui.h

deck.o: deck.h vector.h card.h ui.h

deckTest.o: deck.h  mu_test.h card.h ui.h

hand.o: deck.h  card.h  ADTDefs.h  vector.h  vectorsort.h  hand.h ui.h

handTest.o: deck.h  card.h  ADTDefs.h  vector.h  hand.h  mu_test.h ui.h

player.o: player.h deck.h  card.h  ADTDefs.h  vector.h  vectorsort.h  hand.h ui.h

playerTest.o: player.h deck.h  card.h  ADTDefs.h  vector.h  vectorsort.h  hand.h player.h  mu_test.h ui.h

trick.o: trick.h player.h vector.h vectorsort.h deck.h hand.h card.h ADTDefs.h ui.h

trickTest.o: mu_test.h trick.h player.h vector.h vectorsort.h deck.h hand.h card.h ADTDefs.h ui.h

round.o: trick.h player.h vector.h vectorsort.h deck.h hand.h card.h ADTDefs.h round.h ui.h

roundTest.o:  mu_test.h trick.h player.h vector.h vectorsort.h deck.h hand.h card.h ADTDefs.h round.h ui.h

game.o: trick.h player.h vector.h vectorsort.h deck.h hand.h card.h ADTDefs.h round.h game.h ui.h

gameTest.o: mu_test.h trick.h player.h vector.h vectorsort.h deck.h hand.h card.h ADTDefs.h round.h game.h ui.h

main.o:mu_test.h trick.h player.h vector.h vectorsort.h deck.h hand.h card.h ADTDefs.h round.h game.h ui.h

ui.o: ui.h vector.h deck.h card.h
