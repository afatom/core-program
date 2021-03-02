#include "trick.h"
#include "vector.h"
#include "vectorsort.h"
#include "player.h"
#include "hand.h"
#include "deck.h"
#include "card.h"
#include "ui.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include "ADTDefs.h"

#define TRICK_MAGIC 78952142368 
#define TRUE 1
#define FALSE 0
#define HUMAN__PLAYER 1
#define COMPUTER__PLAYER 0

struct Trick {
    size_t              m_magicNumber;
    Vector*             m_table;
    Player**            m_playersArray;
    size_t              m_playersNumber;
    size_t              m_looserPlayerPoints;
    int                 m_startingPlayer;
    Deck*               m_deck;
};
/**************************************************************************/
static size_t CalcLooserPoints(Vector* _table, Deck* _deck);
static int CheckLooser(Vector* _table, Deck* _deck);

/*UNIT Test Only*/
void TrickAddCardToTable(Trick* trick, int card);
/**************************************************************************/

Trick* TrickCreate( Player** _playersArray, int _startingPlayer, Deck* _deck)
{
    Trick* trick = NULL;
    if(NULL == _playersArray || NULL == *_playersArray || NULL == _deck || _startingPlayer > 3)
    {
        return NULL;
    }
    trick = (Trick*)malloc(sizeof(Trick));
    if(NULL == trick)
    {
        return NULL;
    }
    /*alocating table vector*/
    trick->m_table = VectorCreate(4,0);
    if(NULL == trick->m_table)
    {
        free(trick);
        trick = NULL;
        return NULL;
    }
    /*trick struct initialize*/
    trick->m_magicNumber = TRICK_MAGIC;
    trick->m_playersArray = _playersArray;
    trick->m_playersNumber = 4;
    trick->m_looserPlayerPoints = 0;
    trick->m_startingPlayer = _startingPlayer;
    trick->m_deck = _deck;
    return trick;
}
/********************************************************************/
void TrickDestroy(Trick* _trick)
{
    if(NULL == _trick || _trick->m_magicNumber == 0)
    {
        return;
    }
    _trick->m_magicNumber = 0;
    /*free(_trick->m_table);*/  /*----------------------------Memory leak*/
    _trick->m_playersArray = NULL;
    _trick->m_deck = NULL;
    VectorDestroy(_trick->m_table);
    _trick->m_table = NULL;
    free(_trick);
}
/********************************************************************/
ADTErr TrickRun(Trick* _trick, int* _looserIndex, size_t* _looserPoints)
{
    size_t numberOfThrownCards = 0, pointsCounter =0;
    ADTErr status;
    int looserIndex = 0;
    if(NULL == _trick)
    {
        return ERR_NOT_INITIALIZED;
    }
    if(NULL == _looserIndex || NULL == _looserPoints)
    {
        return ERR_INVALID_DATA_IN;
    }
    VectorItemsNum(_trick->m_table, &numberOfThrownCards);
    /******************************************************************Players play flow*/
    while(numberOfThrownCards < 4 )
    {
        /*******************************************/
        /*PutString("Table Cards__");
        PrintTable(_trick->m_table, _trick->m_deck);*/
        /*sleep(2);*/
        /*******************************************/
        PutString(" ");
        PutString(PlayerGetName(_trick->m_playersArray[_trick->m_startingPlayer]));
        /*sleep(2);*/
        /**************************@@@@@@@@@@*/
        /*check is human*/
        if (IsHumanPlayer(_trick->m_playersArray[_trick->m_startingPlayer]) == TRUE)
        {
            PutString("Table Cards__");
            PrintTable(_trick->m_table, _trick->m_deck);
            /*sleep(2);*/
            if ((status = PlayerPlay(_trick->m_playersArray[_trick->m_startingPlayer], _trick->m_table, HUMAN__PLAYER)) != ERR_OK)
            {
                return status;
            }
            _trick->m_startingPlayer = (_trick->m_startingPlayer + 1) % 4;
            VectorItemsNum(_trick->m_table, &numberOfThrownCards);
        }
        else
        {
            if ((status = PlayerPlay(_trick->m_playersArray[_trick->m_startingPlayer], _trick->m_table, COMPUTER__PLAYER)) != ERR_OK)
            {
                return status;
            }
            /*********************/

            /*********************/
            _trick->m_startingPlayer = (_trick->m_startingPlayer + 1) % 4;
            VectorItemsNum(_trick->m_table, &numberOfThrownCards);
            /*++numberOfThrownCards;*/
        }
    }
    PutString("Table Cards__");
    PrintTable(_trick->m_table, _trick->m_deck);
    /*check who looses*/
    looserIndex = CheckLooser(_trick->m_table, _trick->m_deck);
    *_looserIndex = looserIndex;

    /*calcs points*/
    pointsCounter = CalcLooserPoints(_trick->m_table, _trick->m_deck);
    *_looserPoints = pointsCounter;
    
    /*************print who losses and his points***************/
    /*sleep(1);*/
    PrintPlayerScore(PlayerGetName(_trick->m_playersArray[looserIndex]), pointsCounter);
    /*sleep(1);*/
    /***********************************************************/
    /*update looser player points*/
    /*PlayerAddTrickPoints(_trick->m_playersArray[looserIndex], pointsCounter);*/
    /*return looser index and points to round module*/
    return ERR_OK;
}

/*check who looses static func*/
static int CheckLooser(Vector* _table, Deck* _deck)
{
    int i;
    int index, looserIndex;
    const Card* pCard = NULL;
    Card arr[4];
    Rank higestCard;
    for(i=0; i < 4; ++i)
    {
        VectorGet(_table,(size_t)i,&index);
        pCard = GetCard(index, _deck);
        arr[i] = *((Card*)pCard);
    }
    /*check the higest rank*/
    higestCard = arr[0].rank;
    looserIndex = 0;
    for(i = 0; i<4; ++i)
    {
        if(arr[i].rank > higestCard)
        {
            looserIndex = i;
            higestCard = arr[i].rank;
            return i;
        }        
    }
    return looserIndex;
} 

static size_t CalcLooserPoints(Vector* _table, Deck* _deck)
{
    size_t i, pointsCounter =0;
    int index;
    const Card* pCard = NULL;
    Card arr[4];
    for(i=0; i < 4; ++i)
    {
        VectorGet(_table,i,&index);
        pCard = GetCard(index, _deck);
        arr[i] = *((Card*)pCard);
    }

    for(i = 0; i<4; ++i)
    {
        if(arr[i].suit == HEARTS)
        {
            ++pointsCounter;
        }
        if(arr[i].suit == SPADES && arr[i].rank == RANK_QUEEN)
        {
            pointsCounter+=13;
        }
    }
    return pointsCounter;
} 

/********************************************************************/
void TrickAddCardToTable(Trick* trick, int card)
{
    VectorAdd(trick->m_table,card);
}