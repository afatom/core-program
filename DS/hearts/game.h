#ifndef _GAME_H_
#define _GAME_H_

#include "ADTDefs.h"

typedef struct Game Game;

/*******************************************************************************
*[Description]:Creating Hearts Game. 
*[Input]:Void (4 players only). 
*[return]:in success case Game pointer will be returned.And in any other situation
*NULL will be returned. 
*[Errors]:ERR_INVALID_INPUTS, ERR_ALOCATION_FAILED (failure in memory allocation)
*******************************************************************************/
Game*   GameCreate(void);

/*******************************************************************************
*[Description]:Calling this function will run the game (Like Deal option) in the
*original game.  
*[Input]:Game pointer.
*[return]:in success case Game will start and ERR_OK will be returned in failure
*situation an appropriate error will be returned.
*[Errors]:
*Success Case: ERR_OK.
*Failure Case:__________________________________:
*GENERAL ERRORS->           ERR_GENERAL
*NULL GAME POINTER->        ERR_NOT_INITIALIZED
*MEMMORY FILURE->           ERR_ALLOCATION_FAILED
*******************************************************************************/
ADTErr RunGame(Game* _game);

/*******************************************************************************
*[Description]:Destroying Hearts Game. In NULL game pointer Or in Double free case
*NULL will be returned. 
*[Input]:Game pointer.
*[return]:Void.
*[Errors]:No ERRors return.
*******************************************************************************/
void GameDestroy(Game *_game);

    /***************************/
    /*  UNIT TEST FUNC ONLY    */
    /***************************/
    /*******************************************************************************
*[Description]:Printing Updated game level for unit test isuues only. printing
*round number, players and there points..etc. 
*[Input]:Game pointer.
*[return]:Void.
*[Errors]:No ERRors return.
*******************************************************************************/
    void PrintGame(Game *_game);

#endif /*"_GAME_H_"*/