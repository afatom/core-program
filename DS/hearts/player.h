#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "ADTDefs.h"
#include "deck.h"
#include "vector.h"


typedef struct Player Player;

/*******************************************************************************
*[Description]:Creating One player with aunique identity (unique name). 
*[Input]:player name and player type (human = 1, computer = 0).
*[return]:in success case player pointer will be returned.And in any other situation
*NULL will be returned. 
*[Errors]:NON
*******************************************************************************/
Player* PlayerCreate(const char* _playerName, int _playerType);

/*******************************************************************************
*[Description]:Destroying player module, and hand module. In NULL player pointer 
*Or in Double free case NULL will be returned. 
*[Input]:player pointer.
*[return]:Void.
*[Errors]:No ERRors return.
*******************************************************************************/
void PlayerDestroy(Player * _player);

/*******************************************************************************
*[Description]:This function returns player name.  
*[Input]:player pointer.
*[return]:name.
*[Errors]:No ERRors return.
*******************************************************************************/
const char* PlayerGetName(Player* _player);

/*******************************************************************************
*[Description]:Take One card from round in the begining of each round 13 cards 
*will pass by round to me. after taking the card we will pass it to hand module.
*[Input]:card and pointer to the wright player.
*[return]:ADTErr
*[Errors]:success case ERR_OK.
*Failure Case:__________________________________:
*GENERAL ERRORS->           ERR_GENERAL
*NULL PLAYER POINTER->      ERR_NOT_INITIALIZED
*OVERFLOW FILURE->          ERR_OVERFLOW
*BAD/INVALID CARD->         ERR_INVALID_INPUT
*******************************************************************************/
ADTErr PlayerInsertCard(Player* _player, int _cardIndex);

/*******************************************************************************
*[Description]:Throw One card from Hand module in the begining of each Trick. 
*[Input]:Player pointer and card pointer for derefernce it and putting in it the 
*thrown card.
*[return]:ADTErr status
*[Errors]:success case ERR_OK.
*Failure Case:__________________________________:
*GENERAL ERRORS->           ERR_GENERAL (NULL poiter was passed to me)
*NULL PLAYER POINTER->      ERR_NOT_INITIALIZED
*UNDERFLOW FILURE->         ERR_UNDERFLOW
*******************************************************************************/
ADTErr PlayerPlay(Player* _player, Vector* _table, int _playerType);

/*******************************************************************************
*[Description]:Pass Three cards from hand module in the begining of each round. 
*[Input]:Player pointer and pointer to the begining of array cards to wright in to
*there. caller is responsible for allocating enough space for  three cards. 
*[return]:ADTErr status
*[Errors]:success case ERR_OK.
*Failure Case:__________________________________:
*GENERAL ERRORS->           ERR_GENERAL (NULL poiter was passed to me)
*NULL PLAYER POINTER->      ERR_NOT_INITIALIZED
*******************************************************************************/
ADTErr PlayerPassThreeCards(Player *_player, int *_cardsArr, int _playerType);
    /*******************************************************************************
*[Description]:Creating hand module.
*[Input]:player pointer and deck pointer.
*[return]:ADTErr status
*[Errors]:success case ERR_OK.
*Failure Case:__________________________________:
*NULL PLAYER POINTER->      ERR_NOT_INITIALIZED
*MEMMORY FILURE->           ERR_ALLOCATION_FAILED
*******************************************************************************/
    ADTErr PlayerInitRound(Player *_player, Deck *_deck);

/*******************************************************************************
*[Description]:Updating tottal and round points and Destroying hand module.
*[Input]:player pointer
*[return]:void
*[Errors]:NONE
*******************************************************************************/
ADTErr PlayerEndRound(Player *_player);

/*******************************************************************************
*[Description]:Returning Updated tottal score. 
*[Input]:player pointer.
*[return]:Player score.
*[Errors]:NONE
*******************************************************************************/
size_t PlayerGetTottalPoints(Player* _player);

/*******************************************************************************
*[Description]:Returning Updated Round score. 
*[Input]:player pointer.
*[return]:Player score.
*[Errors]:NONE
*******************************************************************************/
size_t PlayerGetRoundPoints(Player* _player);

/*******************************************************************************
*[Description]:Adding points from trick module at the end of each trick.
*[Input]:player pointer and the num of points
*[return]:ERR status
*[Errors]:success case ERR_OK.
*Failure Case:__________________________________:
*NULL PLAYER POINTER->      ERR_NOT_INITIALIZED
*******************************************************************************/
ADTErr PlayerAddTrickPoints(Player *_player, size_t _points);

/*******************************************************************************
*[Description]:This function takes pointer to player and check if this player got 
*rank 2 , suit clubs card.
*[Input]:player pointer (the player to ask) 
*[return]:0 = I dont have this card. 1 = I have this card.
*[Errors]:NONE
*******************************************************************************/
int IsClubs2CardExistInMyHand(Player* _player);

/*******************************************************************************
*[Description]:This function takes pointer to player and check if this player is
*human or not. 
*[Input]:player pointer (the player to ask) 
*[return]:0 = Computer player. 1 = human player.
*[Errors]:NONE
*******************************************************************************/
int IsHumanPlayer(const Player *_player);

#endif /*_PLAYER_H_*/