#ifndef _TRICK_H_
#define _TRICK_H_

#include "deck.h"
#include "player.h"
#include "vector.h"

typedef struct Trick Trick;

/*******************************************************************************
*[Description]:Create Trick module. round is responsible for creating and destroying
*this module. round must link trick to players array by passing pointer or adress
*of players array (round receive players array adress from game module).     
*[Inputs]:num of players and adress of players array. 
*[return]:Trick pointer or null pointer.
*[Errors]:No errors return.
*******************************************************************************/
Trick* TrickCreate(Player** _playersArray, int _startingPlayer, Deck* _deck);

/*******************************************************************************
*[Description]:Destroying trick module.     
*[Inputs]:Trick pointer.
*[return]:Void no return..
*[Errors]:No errors return.
*******************************************************************************/
void TrickDestroy(Trick* _trick);



ADTErr TrickRun(Trick* _trick, int* _looserIndex, size_t* _looserPoints);


/*unit test only*/
void TrickAddCardToTable(Trick* _trick, int card);


/*******************************************************************************
*[Description]:this function answere the caller (round call for this function),
*after trick ends, and return adress of the looser player and the amount of points
*wich will pass to the looser player. 
*[Inputs]:Trick pointer and player pointer (answere will be settle in this pointer)
* and pointer to fill points. 
*[return]:ADTErr
*[Errors]:
*******************************************************************************/
/*
ADTErr TrickResults(Trick *_trick, Player* _player, size_t *_looserPoints);*/


#endif /*_TRICK_H_*/