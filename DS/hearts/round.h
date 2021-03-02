#ifndef _ROUND_H_
#define _ROUND_H_
#include "ADTDefs.h"
#include "player.h"

/*Direction of play*/
typedef enum {
    RIGHT    =0,
    LEFT,
    ACCROS,
    NO_SWITCH
}SwitchCards;

typedef struct Round Round;

/*******************************************************************************
*[Description]:Creating Game Round. Round Is amajor module, and its responsibilities
*is:
*1.Creating and Comunicating with Deck Module (for dealing cards).
*2.Passing cards to the players.
*3.Creating and Comunicating with Trick Module (for asingle trick and for calculating points
*and discovering looser player).
*Communicating with Players Module and manage evrey trick.  
*[Input]:Number of tottal players, number of rounds to be played.
*[return]:in success case Round pointer will be returned. And in any other failure situation
*NULL will be returned. 
*[Errors]:NONE
*******************************************************************************/

Round *RoundCreate(Player** _playersArray, SwitchCards _beginPlayer);


/*******************************************************************************
*[Description]:Destroying Round module, Trick, Deck modules. In NULL Round pointer 
*Or in Double free case NULL will be returned. 
*[Input]:Round pointer.
*[return]:Void.
*[Errors]:No ERRors return.
*******************************************************************************/
void RoundDestroy(Round* _round);

/*******************************************************************************
*[Description]:Runing One round Of the game and starting the round from aspecific 
*player, this data will be received from Game app. 
*[Input]:Round pointer, players array 
*[return]:ADTErr status.
*[Errors]:
*Success Case: ERR_OK.
*Failure Case:__________________________________:
*GENERAL ERRORS->           ERR_GENERAL
*NULL ROUND POINTER->       ERR_NOT_INITIALIZED
*NULL PLAYER POINTER->      ERR_NOT_INITIALIZED
*MEMMORY FILURE->           ERR_ALLOCATION_FAILED
*******************************************************************************/
ADTErr RoundRunTheGame(Round *_round);


#endif /*_ROUND_H_*/