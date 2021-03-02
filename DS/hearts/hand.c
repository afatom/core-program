#include "hand.h"
#include "vector.h"
#include <stdlib.h>
#include "card.h"
#include "deck.h"
#include "ADTDefs.h"
#include "vectorsort.h"
#include <stdio.h>
#include "ui.h"
#include <unistd.h>


#define HAND_MAGIC          852147963
#define HAND_NUM_OF_CARDS   52
#define HEARTS_SUIT         0
#define CLUBS_SUIT          1
#define DIAMOND_SUIT        3
#define SPADES_SUIT         2
#define HUMAN_PLAYER_       1
#define COMPUTER_PLAYER_    0
#define DOES_NOT_EXIST      0
#define EXIST               1
#define TRUE                1
#define FALSE               0

#define EMPTY 1

/*******************************************************************************/
struct Hand {
    size_t  m_magicNumber;
    Vector* m_suits[4];
    size_t  m_roundPoints;
    size_t  m_trickPoints;
    Deck*   m_deck;
};
/*static ADTErr SmartHandPlay(Hand *_hand, Vector *_table);*/
/*******************************************************************************/
/*static ADTErr PlayEmptyTable(Hand *_hand, Vector *_table);*/
static ADTErr PlayFirstSuitOnTable(Hand *_hand, Vector* _table);
static void swap(Vector* vec);
static void swapFrom(Vector *vec, size_t _fromIndex);
static void ThrowLowestCard(Hand* _hand, Vector* _table ,int _suit);
static void ThrowHumanCard(Hand *_hand, Vector *_table, int _humanCardIndex);
static int IsCardExist(Hand *_hand, int _humanCardIndex);
static int IsEmptyTable(Vector* _table);
static int IsSuitVectorEmpty(Hand *_hand,Vector* _table, int _humanCardIndex);
static int IsSuitMatch(Hand* _hand, Vector *_table, int _humanCardIndex);
static void TakeHumanCard(Hand *_hand, int* _arr, int _humanCardIndex);
static void ThrowRandCard(Hand *_hand, Vector *_table);


/*******************************************************************************/

Hand *HandCreate(Deck* _deck)
{
    int i ,j;
    Hand* handPtr = NULL;
    if(NULL == _deck)
    {
        return NULL;
    }
    handPtr = (Hand*)malloc(sizeof(Hand));
    if(NULL == handPtr)
    {
        return NULL;
    }
    for(i = 0; i < 4; ++i)
    {
        handPtr->m_suits[i] = VectorCreate(16,0);
    }
    /***************** check NULLS ************/
    for(i = 0; i < 4; ++i)
    {
        if(handPtr->m_suits[i] ==NULL)
        {
            for(j = 0; j < i; ++j)
            {
                VectorDestroy(handPtr->m_suits[j]);
            }
            free(handPtr);
            return NULL;
        }
    }
    /***************************************/
    handPtr->m_roundPoints = 0;
    handPtr->m_trickPoints = 0;
    handPtr->m_magicNumber = HAND_MAGIC;
    handPtr->m_deck = _deck;
    return handPtr;
}

/*******************************************************************************/
void HandDestroy(Hand *_hand)
{
    int i;
    if(NULL == _hand || _hand->m_magicNumber == 0)
    {
        return;
    }
    _hand->m_magicNumber = 0;
    for(i = 0; i < 4; ++i)
    {
        VectorDestroy(_hand->m_suits[i]);
    }
    free(_hand);
}
/**********************************************************************************/
ADTErr HandAddTrickPoints(Hand* _hand, size_t _points)
{
    if(NULL == _hand)
    {
        return ERR_NOT_INITIALIZED;
    }
    _hand->m_trickPoints = _points;
    _hand->m_roundPoints += _points;
    return ERR_OK; 
}
/**********************************************************************************/
size_t HandGetRoundPoints(Hand* _hand)
{
    if(NULL == _hand)
    {
        return ERR_NOT_INITIALIZED;
    }
    return _hand->m_roundPoints;
}
/**********************************************************************************/
ADTErr HandInsertCard(Hand* _hand, int _cardIndex)
{
    int i;
    const Card* inCard = NULL;
    ADTErr status;
    if(NULL == _hand)
    {
        return ERR_NOT_INITIALIZED;
    }
    if((_cardIndex < 0 || _cardIndex > HAND_NUM_OF_CARDS-1))
    {
        return ERR_INVALID_DATA_IN;
    }
    /*check card suit*/
    inCard = GetCard(_cardIndex, _hand->m_deck);
    switch (inCard->suit)
    {
        case HEARTS:
        if((status = VectorAdd(_hand->m_suits[0], _cardIndex)) != ERR_OK)
        {
            return status;
        }
        break;
        /***************************/
        case DIAMOND:
        if((status = VectorAdd(_hand->m_suits[3], _cardIndex)) != ERR_OK)
        {
            return status;
        }
        break;
        /***************************/
        case SPADES:
        if((status = VectorAdd(_hand->m_suits[2], _cardIndex)) != ERR_OK)
        {
            return status;
        }
        break;
        /***************************/
        case CLUBS:
        if((status = VectorAdd(_hand->m_suits[1], _cardIndex)) != ERR_OK)
        {
            return status;
        }
        break;

        default: break;
    }
    /*sort vector by rank before return*/
    for(i = 0; i < 4; ++i)
    {
        InsertionSort(_hand->m_suits[i]);
    }
   
    return ERR_OK;
}
/**********************************************************************************/
ADTErr HandPlay(Hand* _hand, Vector* _table, int _playerType)
{
    int firstCardIndex;
    int humancardindex;
    const Card *firstCard = NULL;
    /*************************************/
    if(NULL == _hand)
    {
        return ERR_NOT_INITIALIZED;
    }
    if(_table == NULL)
    {
        return ERR_INVALID_DATA_IN;
    }

    /***********************************************************************/
    PutString(" ");
    PutString("My Hand Cards Before__");
    PrintHandCards(_hand->m_suits, _hand->m_deck);
    /*sleep(1);*/
    /***********************************
    is human type, if yes ask him to throw card and check rules
    if not , throw card
    ************************************/
    if (_playerType == HUMAN_PLAYER_)
    {
        /*
        PutString("Your Currently Hand Cards-->>");
        PrintHandCards(_hand->m_suits, _hand->m_deck);*/
        while(1)
        {
            humancardindex = GetHumanCard(_hand->m_deck);
            
            if (IsCardExist(_hand, humancardindex) == DOES_NOT_EXIST)
            {
                continue;
            }
            if (IsEmptyTable(_table)==TRUE)
            {
                if (IsClubs2CardExist(_hand) == EXIST)
                {
                    /*throw clubs 2*/
                    firstCard = GetCard(humancardindex, _hand->m_deck);
                    if (RANK_2 == firstCard->rank && CLUBS == firstCard->suit)
                    {
                        ThrowHumanCard(_hand, _table, humancardindex);
                        return ERR_OK;
                    }
                    else
                    {
                        continue;
                    }
                }
                else
                {
                    ThrowHumanCard(_hand, _table, humancardindex);
                    return ERR_OK;
                }
            }
            else /*************************************************/
            {
                #ifdef NDEBUG
                puts("hand.c mod Issuitempty");
                #endif
                if ((IsSuitVectorEmpty(_hand,_table ,humancardindex) == EMPTY))
                {
                    #ifdef NDEBUG
                    puts("$$$$$$$$$$$");
                    #endif

                    #ifdef NDEBUG
                    puts("hand.c hand play Empty suit vector");
                    printf("Human card index %d\n",humancardindex);
                    #endif
                    ThrowHumanCard(_hand, _table, humancardindex);
                    return ERR_OK;
                }         
              
                else
                {
                    #ifdef NDEBUG
                    puts("---@--@--@");
                    #endif
                    if (IsSuitMatch(_hand, _table, humancardindex)==TRUE)
                    {
                        ThrowHumanCard(_hand, _table, humancardindex);
                        return ERR_OK;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
    }
    /*check if there is no cards on the table*/
    if(VectorGet(_table, 0, &firstCardIndex)== ERR_WRONG_INDEX)
    {
        /*return PlayEmptyTable(_hand, _table);*/
        if (IsClubs2CardExist(_hand) == EXIST)
        {
            ThrowLowestCard(_hand, _table, CLUBS_SUIT);
            return ERR_OK;
        }
        ThrowRandCard(_hand, _table);
        return ERR_OK;
    }
    return PlayFirstSuitOnTable(_hand, _table);
    /***********************************************************************/
}

/**********************************************************************************/

void HandPrintCards(Hand* _hand)
{   
    if(NULL == _hand)
    {
        puts("Empty hand !");
    }
    puts("Hearts Vector:");
    VectorPrint(_hand->m_suits[0]);
    puts("Clubs Cards:");
    VectorPrint(_hand->m_suits[1]);
    puts("Diamonds Cards:");
    VectorPrint(_hand->m_suits[3]);
    puts("Spades Cards:");
    VectorPrint(_hand->m_suits[2]);
}

/**********************************************************************************/

ADTErr HandThrow3Cards(Hand *_hand, int *_cardsArr, int _playerType)
{
    size_t numOfCards = 0, counter = 0;
    int j = 0, q;
    /*int firstCardIndex;*/
    int humancardindex;
    /*const Card *firstCard = NULL;
    */
    /*check if vector[suit] is empty */

    if (NULL == _hand)
    {
        return ERR_NOT_INITIALIZED;
    }

    if (NULL == _cardsArr)
    {
        return ERR_INVALID_DATA_IN;
    }

    if (_playerType == HUMAN_PLAYER_)
    {
        PutString("Your Currently Hand Cards-->>");
        PrintHandCards(_hand->m_suits, _hand->m_deck);
        while (counter < 3)
        {
            humancardindex = GetHumanCard(_hand->m_deck);
            if (IsCardExist(_hand, humancardindex) == DOES_NOT_EXIST)
            {
                continue;
            }
            TakeHumanCard(_hand, _cardsArr + (int)counter, humancardindex);
            ++counter;
        }
    }
    
    /****************** computer player */
    q = rand() % 4;

    while (counter < 3)
    {
        VectorItemsNum(_hand->m_suits[q], &numOfCards);
        if (numOfCards > 1)
        {
            VectorDelete(_hand->m_suits[q], (_cardsArr + j));
        }
        ++counter;
        ++j;
        q = (q+1) % 4;
    }

    /*sort vector by rank before return*/
    for (j = 0; j < 4; ++j)
    {
        InsertionSort(_hand->m_suits[j]);
    }
    return ERR_OK;
}
    /**********************************************************************************/
    int IsClubs2CardExist(Hand * _hand)
    {
        int firstCardIndex;
        const Card *firstCard = NULL;
        size_t _numOfItems;
        if (NULL == _hand)
        {
            return 0;
        }

        VectorItemsNum(_hand->m_suits[CLUBS_SUIT], &_numOfItems);
        if (_numOfItems == 0)
        {
            return DOES_NOT_EXIST;
        }

        VectorGet(_hand->m_suits[CLUBS_SUIT], 0, &firstCardIndex);
        firstCard = GetCard(firstCardIndex, _hand->m_deck);

        if (firstCard->rank != RANK_2)
        {

            return DOES_NOT_EXIST;
        }

        return EXIST;
    }

    /*****************************************************************************/
   /*
    static ADTErr PlayEmptyTable(Hand * _hand, Vector * _table)
    {
        

        const Card *firstCard = NULL;
        int firstClubCard;
        VectorGet(_hand->m_suits[CLUBS], 0, &firstClubCard);
        firstCard = GetCard(firstClubCard, _hand->m_deck);

        if (RANK_2 == firstCard->rank)
        {
            ThrowLowestCard(_hand, _table, CLUBS_SUIT);
            return ERR_OK;
        }
        
        if (IsEmptyVector(_hand->m_suits[CLUBS_SUIT]) && IsEmptyVector(_hand->m_suits[SPADES_SUIT]) && IsEmptyVector(_hand->m_suits[DIAMOND_SUIT]))
        {
            ThrowLowestCard(_hand, _table, HEARTS_SUIT);
        }
        else if (IsEmptyVector(_hand->m_suits[CLUBS_SUIT]))
        {
            ThrowLowestCard(_hand, _table, CLUBS_SUIT);
        }
        else if (IsEmptyVector(_hand->m_suits[SPADES_SUIT]))
        {
            ThrowLowestCard(_hand, _table, SPADES_SUIT);
        }
        else
        {
            ThrowLowestCard(_hand, _table, DIAMOND_SUIT);
        }
        return ERR_OK;
    }
*/
    /*****************************************************************************/
    static ADTErr PlayFirstSuitOnTable(Hand * _hand, Vector * _table)
    {
        int firstCardIndex, i;
        const Card *firstCard = NULL;
        /*check the suit of first card*/
        VectorGet(_table, 0, &firstCardIndex);
        firstCard = GetCard(firstCardIndex, _hand->m_deck);
        if (!IsEmptyVector(_hand->m_suits[firstCard->suit]))
        {
            ThrowLowestCard(_hand, _table, firstCard->suit);
            return ERR_OK;
        }
        for (i = 0; i < 4; ++i)
        {
            /*is empty*/
            if (!IsEmptyVector(_hand->m_suits[(firstCard->suit + i) % 4]))
            {
                ThrowLowestCard(_hand, _table, (firstCard->suit + i) % 4);
                return ERR_OK;
            }
        }
        return ERR_UNDERFLOW;
    }

    /*****************************************************************************/
    static void swap(Vector * vec)
    {
        int templast, tempfirst;
        size_t numOfItems;
        VectorItemsNum(vec, &numOfItems);
        VectorGet(vec, numOfItems - 1, &templast);
        VectorGet(vec, 0, &tempfirst);
        VectorSet(vec, 0, templast);
        VectorSet(vec, numOfItems - 1, tempfirst);
    }

    /*****************************************************************************/
    static void swapFrom(Vector * vec, size_t _fromIndex)
    {
        int templast, tempfirst;
        size_t numOfItems;
        VectorItemsNum(vec, &numOfItems);
        VectorGet(vec, numOfItems - 1, &templast);
        VectorGet(vec, _fromIndex, &tempfirst);
        VectorSet(vec, _fromIndex, templast);
        VectorSet(vec, numOfItems - 1, tempfirst);
    }

    /*****************************************************************************/
    static void ThrowLowestCard(Hand * _hand, Vector * _table, int _suit)
    {
        int thrownCardIndex;
        /*Throw the lowest card*/
        /*swap*/
        swap(_hand->m_suits[_suit]);
        /*throw*/
        VectorDelete(_hand->m_suits[_suit], &thrownCardIndex);
        VectorAdd(_table, thrownCardIndex);
        /*sort again*/
        InsertionSort(_hand->m_suits[_suit]);
    }

    static void ThrowRandCard(Hand *_hand, Vector *_table)
    {
        int thrownCardIndex=0, _suit=0;
        _suit = rand() % 4;
        #ifdef NDEBUG
        printf("at hand.c throwrandcard Suit = %d\n",_suit);
        #endif
        while (IsEmptyVector(_hand->m_suits[_suit]))
        {
            _suit = (_suit+1) % 4;
        }
        
        VectorDelete(_hand->m_suits[_suit], &thrownCardIndex);
        VectorAdd(_table, thrownCardIndex);
        /*sort again*/
        InsertionSort(_hand->m_suits[_suit]);
        return;
    }

    /*****************************************************************************/
    static void ThrowHumanCard(Hand * _hand, Vector * _table, int _humanCardIndex)
    {
        const Card *humanCard = NULL;
        size_t numOfCards, Index;
        int getResult, thrownCardIndex;

        humanCard = GetCard(_humanCardIndex, _hand->m_deck);
        VectorItemsNum(_hand->m_suits[humanCard->suit], &numOfCards);

        while (numOfCards != 0)
        {
            VectorGet(_hand->m_suits[humanCard->suit], numOfCards -1, &getResult);
            if (_humanCardIndex == getResult)
            {
                Index = numOfCards -1;
                break;
            }
            --numOfCards;
        }
        swapFrom(_hand->m_suits[humanCard->suit], Index);

        VectorDelete(_hand->m_suits[humanCard->suit], &thrownCardIndex);
        VectorAdd(_table, _humanCardIndex);
        /*sort again*/
        InsertionSort(_hand->m_suits[humanCard->suit]);
    }

    static void TakeHumanCard(Hand *_hand, int* _arr, int _humanCardIndex)
    {
        const Card *humanCard = NULL;
        size_t numOfCards, Index;
        int getResult, thrownCardIndex;

        humanCard = GetCard(_humanCardIndex, _hand->m_deck);
        VectorItemsNum(_hand->m_suits[humanCard->suit], &numOfCards);

        while (numOfCards != 0)
        {
            VectorGet(_hand->m_suits[humanCard->suit], numOfCards - 1, &getResult);
            if (_humanCardIndex == getResult)
            {
                Index = numOfCards - 1;
                break;
            }
            --numOfCards;
        }
        swapFrom(_hand->m_suits[humanCard->suit], Index);

        VectorDelete(_hand->m_suits[humanCard->suit], &thrownCardIndex);
        *_arr= _humanCardIndex;
        /*sort again*/
        InsertionSort(_hand->m_suits[humanCard->suit]);
    }

    /*****************************************************************************/
    /*
static ADTErr ThrowSpadesQueen(Hand *_hand, Vector *_table)
{
   
    int firstCardIndex;
    int secCard;
    const Card *firstCard = NULL;
    const Card *secCardptr = NULL;

    size_t numOfCardsOnTable;
    VectorGet(_table, 0, &firstCardIndex);
    firstCard = GetCard(firstCardIndex,_hand->m_deck);
    VectorItemsNum(_table, &numOfCardsOnTable);
    if (numOfCardsOnTable >= 2 && firstCard->suit ==SPADES && firstCard->rank == RANK_QUEEN)
    {
        if (numOfCardsOnTable == 2)
        {
            secCard = GetCard(secCard, _hand->m_deck);
            if (secCardptr->suit == SPADES && (secCardptr->rank == RANK_KING ||secCardptr->rank == RANK_ACE))
            {
                
            }
            
        }

    }


}*/

    /*****************************************************************************/
    static int IsCardExist(Hand * _hand, int _humanCardIndex)
    {
        const Card *humanCard = NULL;
        size_t numOfCards;
        int getResult;
        humanCard = GetCard(_humanCardIndex, _hand->m_deck);
        if (VectorItemsNum(_hand->m_suits[humanCard->suit], &numOfCards) != ERR_OK)
        {
            return DOES_NOT_EXIST;
        }
        while (numOfCards != 0)
        {
            VectorGet(_hand->m_suits[humanCard->suit], numOfCards - 1, &getResult);
            if (_humanCardIndex == getResult)
            {
                return EXIST;
            }
            --numOfCards;
        }
        return DOES_NOT_EXIST;
    }

    /*****************************************************************************/
    static int IsEmptyTable(Vector * _table)
    {
        return IsEmptyVector(_table);
    }

    /*****************************************************************************/
    static int IsSuitVectorEmpty(Hand *_hand,Vector* _table, int _humanCardIndex)
    {
        const Card *humanCard = NULL;
        int firstTableCard = 0;
        VectorGet(_table,0,&firstTableCard);
        humanCard = GetCard(firstTableCard, _hand->m_deck);
        #ifdef NDEBUG
        printf("Suit is num ::%d\n",((Card *)humanCard)->suit);
        printf("Hand.c 641  is empty vector :: %d\n",IsEmptyVector(_hand->m_suits[((Card *)humanCard)->suit]));
        #endif

        if (IsEmptyVector(_hand->m_suits[((Card *)humanCard)->suit]) == EMPTY)
        {
            return TRUE;
        }
        return FALSE;
    }

    /*****************************************************************************/
    static int IsSuitMatch(Hand * _hand, Vector * _table, int _humanCardIndex)
    {
        const Card *humanCard = NULL;
        const Card *tableFirstCard = NULL;
        int tableFirstCardIndex;
        humanCard = GetCard(_humanCardIndex, _hand->m_deck);
        VectorGet(_table, 0, &tableFirstCardIndex);
        tableFirstCard = GetCard(tableFirstCardIndex, _hand->m_deck);
        if (!(humanCard->suit == tableFirstCard->suit))
        {
            return FALSE;
        }
        return TRUE;
    }
    /*****************************************************************************/
