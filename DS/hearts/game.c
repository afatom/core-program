#include "game.h"
#include <stdlib.h>         /*Malloc, Size_t*/
#include <stdio.h>
#include "player.h"
#include "round.h"
#include "ui.h"
#include "ADTDefs.h"
#include <unistd.h>

#define GAME_MAGIC 531773349
#define HUMAN_PLAYER 1
#define COMPUTER_PLAYER 0
#define MAX_NAME 10


struct Game {
    size_t      m_magicNumber;  /*Avoid Double Free*/
    Round*      m_round;
    Player*     m_players[4];
    size_t      m_tottalPoints;
};


/*******************************************************************************/
Game*   GameCreate(void)
{
   
    char str[11]="a";
    Game* game = NULL;
    /*create game*/
    game = (Game*)malloc(sizeof(Game));
    if(NULL == game)
    {
        return NULL;
    }
    
/*    GetString("Please Enter Your Name (Max Length Name Is 10 letters)", str);*/
    GetPlayerName("Please Enter Your Name (Max Length Name Is 10 letters)", str, MAX_NAME + 1);

    game->m_players[0] = PlayerCreate(str, HUMAN_PLAYER);

    game->m_players[1] = PlayerCreate("Alex", COMPUTER_PLAYER);
    game->m_players[2] = PlayerCreate("Jhon", COMPUTER_PLAYER);
    game->m_players[3] = PlayerCreate("Petter", COMPUTER_PLAYER);
    game->m_round = NULL;
    game->m_magicNumber = GAME_MAGIC;
    game->m_tottalPoints = 0;
    return game;
}
/*******************************************************************************/
void GameDestroy(Game *_game)
{
    int i;
    if(NULL == _game || _game->m_magicNumber == 0)
    {
        return;
    }
    for(i=0; i < 4; ++i)
    {
        PlayerDestroy(_game->m_players[i]);
    }
    _game->m_magicNumber = 0;
    _game->m_round = NULL;
    free(_game);
    _game=NULL;
}
/*******************************************************************************/
ADTErr RunGame(Game *_game)
{
    ADTErr status;
    int i, j=0;
    if(NULL == _game)
    {
        return ERR_NOT_INITIALIZED;
    }

    while (j<3)
    {
        _game->m_round =  RoundCreate(_game->m_players,0);
        if((status = RoundRunTheGame(_game->m_round) != ERR_OK))
        {
            return status;
        }
        for(i = 0; i < 4; ++i)
        {
            if(PlayerGetTottalPoints(_game->m_players[i]) == 100)
            {
                /*looser. printf*/
                break;
            }
        }

        RoundDestroy(_game->m_round);
        ++j;
        sleep(1);
    }
    return ERR_OK;
}
/***************************/
/*  UNIT TEST FUNC ONLY    */
/***************************/
/******************************************************************************/
void PrintGame(Game * _game);