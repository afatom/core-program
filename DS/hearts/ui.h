#ifndef _UI_H_
#define _UI_H_

#include "vector.h"
#include "deck.h"
#include "card.h"
#include <stdlib.h>


void PrintColoredCard(const Card* _card);

void PrintPlayerCards(Vector** cards, const char* playerName, Deck* _deck);

void PrintTable(Vector *_table, Deck *_deck);

void GetString(const char *msg, char *str);

void GetPlayerName(const char *msg, char *str, int _maxNameLength);

void PrintHandCards(Vector **cards, Deck *_deck);

void PutString(const char *msg);

void PrintPlayerScore(const char* _playerName , size_t _score);

void Print3Cards(int *arr, Deck *_deck);

int GetHumanCard(Deck *_deck);
#endif /*_UI_H_*/