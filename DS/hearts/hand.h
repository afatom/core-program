#ifndef _HAND_H_
#define _HAND_H_

#include "card.h"
#include "ADTDefs.h"
#include "deck.h"
#include <stdlib.h>
#include "vector.h"

typedef struct Hand Hand;

/*******************************************************************************
*[Description]:Creating Hand. Hand will holds cards
*for each round and will play for whole round, manage points for each trick and 
*take Decisions for evrey trick run. and it will update its player for round points
*it will be destroyed at the end of round.    
*[Input]:Deck pointer (for manpulating and converting cards).
*[return]:in success case Hand pointer will be returned. And in any other failure situation
*NULL will be returned. 
*[Errors]:NONE
*******************************************************************************/
Hand *HandCreate(Deck* _deck);

/*******************************************************************************
*[Description]:Destroying Hand Pointer.  
*[Input]:Hand pointer to be destroyed
*[return]:void 
*[Errors]:NONE
*******************************************************************************/
void    HandDestroy(Hand* _hand);

/*******************************************************************************
*[Description]:Adding anew incoming card to hand approprate vector.  
*[Input]:Hand pointer and card index to be inserted.
*[return]:ADTErr 
*[Errors]:
*******************************************************************************/
ADTErr HandInsertCard(Hand* _hand, int _cardIndex);

/*******************************************************************************
*[Description]:For Non Human Players Only, this function will "think" and take
*decision for perfect 3 cards to get rid of them. 
*[Input]:Hand pointer and cards array for return 3 cards.
*[return]:ADTErr
*[Errors]:
*******************************************************************************/
ADTErr HandThrow3Cards(Hand* _hand, int* _cardsArr, int _playerType);

/*******************************************************************************
*[Description]:Adding points by player after ending one trick. 
*[Input]:Hand pointer and points to be added.
*[return]:ADTErr
*[Errors]:
*******************************************************************************/
ADTErr HandAddTrickPoints(Hand* _hand, size_t _points);

/*******************************************************************************
*[Description]:Returning points of acomplete round.  
*[Input]:Hand pointer.
*[return]:amount of points.
*[Errors]:
*******************************************************************************/
size_t HandGetRoundPoints(Hand* _hand);

/*******************************************************************************
*[Description]:For Non Human Players Only, this function will "think" and take
*decision for perfect card to throw. 
*[Input]:Hand pointer and table vector pointer.
*[return]:void 
*[Errors]:NONE
*******************************************************************************/
ADTErr HandPlay(Hand* _hand, Vector* _table, int _playerType);

/*******************************************************************************
*[Description]:this function checks if clubs2 card exist. if yes true = 1 will be 
*returned else 0 will return.
*[Input]:Hand pointer.
*[return]:1 = card exist, 0 = card does not exist.
*[Errors]:NONE
*******************************************************************************/
int IsClubs2CardExist(Hand *_hand);


/************* unit test only ********************/
void HandPrintCards(Hand* _hand);


#endif /*_HAND_H_*/