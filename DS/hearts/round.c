#include "round.h"
#include <stdlib.h> /*Malloc, Size_t*/
#include "player.h"
#include "ADTDefs.h"
#include "trick.h"
#include <unistd.h>
#include "deck.h"
#include <stdio.h>
#include "ui.h"
#include <stdio.h>

#define ROUND_MAGIC 7854123698

/**************************************************************************/
struct Round{
    size_t      m_magicNumber;  /*Avoid Double Free*/
    Trick*      m_trick;
    Deck*       m_deck; 
    Player**    m_players;
    int         m_startingPlayer;
};
/*******************************************************************************/
static ADTErr BuildTrick(Round* round);
static ADTErr Pass3Cards(Round* _round, int _startingPlayer);
/*******************************************************************************/
Round*  RoundCreate(Player** _playersArray, SwitchCards _beginPlayer)
{
    Round* round = NULL;
    if(NULL == _playersArray || NULL == *_playersArray)
    {
        return NULL;
    }
    round = (Round*)malloc(sizeof(Round));
    if(NULL == round)
    {
        return NULL;
    }
    /*create Deck Module*/
    round->m_deck = CreateDeck();
    if(NULL == round->m_deck)
    {
        free(round);
        return NULL;
    }
    /*Create Trick Module*/
    /*
    round->m_trick = TrickCreate(_playersArray, _beginPlayer, round->m_deck);
    if(NULL == round->m_trick)
    {
        DestroyDeck(round->m_deck);
        free(round);
        return NULL;
    }*/
    round->m_magicNumber = ROUND_MAGIC;
    round->m_startingPlayer = _beginPlayer;
    round->m_players = _playersArray;
    return round;
}
/**************************************************************************/
void RoundDestroy(Round* _round)
{
    if(NULL == _round || _round->m_magicNumber == 0)
    {
        return;
    }
    _round->m_magicNumber = 0;
    DestroyDeck(_round->m_deck);
    free(_round);
}
/**************************************************************************/

ADTErr RoundRunTheGame(Round *_round)
{
    int i, j;
    ADTErr insertStatus, status;
    int ThebeginPlayer;
    int stp;
    size_t looserPoints;
    if(NULL == _round)
    {
        
        return ERR_NOT_INITIALIZED;
    }
    PutString("=========================================================================>>>>  New Round Begin ");
    
    stp = _round->m_startingPlayer;
    /************************************************************************************//* players init round */
    for(i = 0; i < 4; ++i)
    {
        if ((status = PlayerInitRound(_round->m_players[i], _round->m_deck)) != ERR_OK)
        {
            return status;
        }
    }
    
    /************************************************************************************************************/
    ShuffleCards(_round->m_deck);

    /******************************************************************************************* Dealing Cards Loop*/
    for(i = 0; i < 13; ++i)
    {
        for(j = 0; j < 4; ++j)
        {
            /*players insert cards*/
            if((insertStatus = PlayerInsertCard(_round->m_players[(stp + j) % 4], DealCard(_round->m_deck))) != ERR_OK) 
            {
                return insertStatus;
            }
        }
    }

    /**********************************************************************************Passing 3 cards*/
    if( (status = Pass3Cards(_round, stp))!=ERR_OK)
    {
        return status;
    }

    /**************************************************************************************** check who have clubs 2 card*/
    PutString("Searching For clubs 2 card");
    
    for (j = 0; j < 4; ++j)
    {
        
        if ((IsClubs2CardExistInMyHand(_round->m_players[(stp + j) % 4])) == 1)
        {
            ThebeginPlayer = stp + j;
          
            _round->m_startingPlayer = ThebeginPlayer;
            /*sleep(1);*/
            PutString(PlayerGetName(_round->m_players[ThebeginPlayer]));
            PutString("Got The Clubs 2 Card");
            /*sleep(1);*/
            
            break;
        }
    }
   
    /************************************* Trick takes controll       ************************** run trick*/
    for (i = 0; i < 13; ++i)
    {
        BuildTrick(_round);
        PutString("=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*");
        PutString("=*=*=*=*=*=*    New Trick Begin     =*=*=*=*=*=*");
        PutString("=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*");
        /*sleep(1);*/
        if((status = TrickRun(_round->m_trick, &(_round->m_startingPlayer), &looserPoints)) != ERR_OK)
        {
            return status;
        }
        PlayerAddTrickPoints(_round->m_players[_round->m_startingPlayer], looserPoints);
        PutString(">>>>>> Players Points For This Trick");
        for(i =0; i<4; ++i)
        {
            PrintPlayerScore(PlayerGetName(_round->m_players[i]), PlayerGetTottalPoints(_round->m_players[i]));
        }
        TrickDestroy(_round->m_trick);
        PutString("=*=*=*=*=*=* =*=*=*=*=*=*     End Trick    =*=*=*=*=*=*=*=*=*=*=*=*");
        /*sleep(1);*/
    }
    
    /********************************************************************************** players end round*/
    for(i = 0; i < 4; ++i)
    {
        if ((status = PlayerEndRound(_round->m_players[i])) != ERR_OK)
        {
            return status;
        }
    }

    PutString("======================================================>>>>  End Round ");
    /*sleep(1);*/
    return ERR_OK;

}
/*******************************************************************************/
/*******************************************************************************/
static ADTErr BuildTrick(Round* round)
{
    round->m_trick = TrickCreate(round->m_players, round->m_startingPlayer, round->m_deck);
    if(NULL == round->m_trick)
    {
        return ERR_ALLOCATION_FAILED;
    }
    return ERR_OK;

}

/*******Static functions*/

static ADTErr Pass3Cards(Round *_round, int _startingPlayer)
{
    int Cards[12] = {0};
    int stp, j, i;
    ADTErr status;
    int *cardsPtr = &Cards[0];

    stp = _startingPlayer;
    stp = 0;
    PutString("       Passing 3 cards Stage      ");

    /******************************************************/ /*<< throwing cards loop*/
    for (j = 0; j < 4; ++j)
    {
        PutString(PlayerGetName(_round->m_players[(stp + j) % 4]));
        if ((status = PlayerPassThreeCards(_round->m_players[(stp + j) % 4],
                                           cardsPtr + 3 * j, IsHumanPlayer(_round->m_players[(stp + j) % 4]))) != ERR_OK)
        {
            return status;
        }
        Print3Cards(cardsPtr + 3 * j, _round->m_deck);
    }
    /*******************************************************/

    /******************************************************/ /*<< Inserting cards loop*/
    cardsPtr = &Cards[0];
    for (j = 0; j < 4; ++j)
    {
        for (i = 0; i < 3; ++i)
        {
            if ((status = PlayerInsertCard(_round->m_players[(stp + j) % 4], *(cardsPtr + (9 + j * 3 + i) % 12))) != ERR_OK)
            {
                return status;
            }
        }
    }
    return ERR_OK;
}
