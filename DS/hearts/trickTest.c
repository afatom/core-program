#include "vector.h"
#include <stdlib.h>
#include "trick.h"
#include "deck.h"
#include "player.h"
#include "hand.h"
#include "mu_test.h"
#include <stdio.h>

/********************************************/
UNIT(Trick_Create_Null_Test)
    Trick* trick = NULL;
    Deck* deck = NULL;
    trick = TrickCreate(NULL, 2, deck);
    ASSERT_THAT(NULL == trick);
END_UNIT
/********************************************/
UNIT(Trick_Create_Normal_Test)
    int i;
    Trick* trick = NULL;
    Deck* deck = NULL;
    Player* arr[4]= {NULL,NULL,NULL,NULL};
    deck = CreateDeck();
    for(i=0; i<4; ++i)
    {
        arr[i] = PlayerCreate("A", 0);
    }

    trick = TrickCreate(arr, 2, deck);
    ASSERT_THAT(NULL != trick);
    for(i=0; i<4; ++i)
    {
        PlayerDestroy(arr[i]);
    }
    DestroyDeck(deck);
    TrickDestroy(trick);
END_UNIT
/********************************************/
UNIT(Trick_Double_Destroy_Test)
    int i;
    Trick* trick = NULL;
    Deck* deck = NULL;
    Player* arr[4]= {NULL,NULL,NULL,NULL};
    deck = CreateDeck();
    for(i=0; i<4; ++i)
    {
        arr[i] = PlayerCreate("A", 0);
    }

    trick = TrickCreate(arr, 2, deck);
    ASSERT_THAT(NULL != trick);
    for(i=0; i<4; ++i)
    {
        PlayerDestroy(arr[i]);
    }
    DestroyDeck(deck);
    TrickDestroy(trick);
    /*TrickDestroy(trick);*/ /*cause bugs*/
END_UNIT

UNIT(Run_Trick_Test)
    int i,j;

    int looserIndex;
    size_t looserPoints;

    Trick* trick = NULL;
    Deck* deck = NULL;
    Player* arr[4]= {NULL,NULL,NULL,NULL};
    deck = CreateDeck();
    for(i=0; i<4; ++i)
    {
        arr[i] = PlayerCreate("A", 0);
    }
    ShuffleCards(deck);
    trick = TrickCreate(arr, 0, deck);
    ASSERT_THAT(NULL != trick);
    
    /*TrickAddCardToTable(trick, 23);*/
    /*******************************************************************/
    /*players init round - build your hands*/
    for(i =0; i<4; ++i)
    {
        ASSERT_THAT( PlayerInitRound(arr[i],deck) == ERR_OK);
    }
    /*******************************************************************/
    /*add cards to players manually*/
    for(i = 0; i < 5; ++i)
    {
        for(j=0; j<4;++j)
        {
            
           ASSERT_THAT(PlayerInsertCard(arr[j], DealCard(deck)) == ERR_OK); 
        }
    }
    /*******************************************************************/
    ASSERT_THAT(TrickRun(trick, &looserIndex, &looserPoints) == ERR_OK);
    printf("looser index %d\n", looserIndex);
    printf("losser points %lu\n", looserPoints);
    /*******************************************************************/
    for(i=0; i<4; ++i)
    {
        PlayerEndRound(arr[i]);
        PlayerDestroy(arr[i]);
    }
    DestroyDeck(deck);
    TrickDestroy(trick);
END_UNIT

UNIT(Run_Few_Trics_Test)
    int i,j;
    int numOfTricks =0;
    int looserIndex;
    size_t looserPoints;

    Trick* trick = NULL;
    Deck* deck = NULL;
    Player* arr[4]= {NULL,NULL,NULL,NULL};
    deck = CreateDeck();
    for(i=0; i<4; ++i)
    {
        arr[i] = PlayerCreate("ABC", 0);
    }
    ShuffleCards(deck);

    while(numOfTricks < 3)
    {
        trick = TrickCreate(arr, 0, deck);
        ASSERT_THAT(NULL != trick);
        
        /*TrickAddCardToTable(trick, 23);*/
        /*******************************************************************/
        /*players init round - build your hands*/
        for(i =0; i<4; ++i)
        {
            ASSERT_THAT( PlayerInitRound(arr[i],deck) == ERR_OK);
        }
        /*******************************************************************/
        /*add cards to players manually*/
        for(i = 0; i < 5; ++i)
        {
            for(j=0; j<4;++j)
            {  
                ASSERT_THAT(PlayerInsertCard(arr[j], DealCard(deck)) == ERR_OK); 
            }
        }
        /*******************************************************************/
        ASSERT_THAT(TrickRun(trick, &looserIndex, &looserPoints) == ERR_OK);
        printf("looser index %d\n", looserIndex);
        printf("losser points %lu\n", looserPoints);
        /*******************************************************************/
        for(i=0; i<4; ++i)
        {
            PlayerEndRound(arr[i]);
        }
        TrickDestroy(trick);
        ++numOfTricks;
    }
    for(i=0; i<4; ++i)
    {
        PlayerDestroy(arr[i]);
    }

    DestroyDeck(deck);
END_UNIT


UNIT(Run_13_Trics_Test)
    int i,j;
    int numOfTricks =0;
    int looserIndex;
    size_t looserPoints;

    Trick* trick = NULL;
    Deck* deck = NULL;
    Player* arr[4]= {NULL,NULL,NULL,NULL};
    deck = CreateDeck();
    for(i=0; i<4; ++i)
    {
        arr[i] = PlayerCreate("ABC", 0);
    }
    ShuffleCards(deck);

    while(numOfTricks < 13)
    {
        trick = TrickCreate(arr, 0, deck);
        ASSERT_THAT(NULL != trick);
        
        /*TrickAddCardToTable(trick, 23);*/
        /*******************************************************************/
        /*players init round - build your hands*/
        for(i =0; i<4; ++i)
        {
            ASSERT_THAT( PlayerInitRound(arr[i],deck) == ERR_OK);
        }
        /*******************************************************************/
        /*add cards to players manually*/
        for(i = 0; i < 13; ++i)
        {
            for(j=0; j<4;++j)
            {  
                ASSERT_THAT(PlayerInsertCard(arr[j], DealCard(deck)) == ERR_OK); 
            }
        }
        /*******************************************************************/
        ASSERT_THAT(TrickRun(trick, &looserIndex, &looserPoints) == ERR_OK);
        printf("looser index %d\n", looserIndex);
        printf("losser points %lu\n", looserPoints);
        /*******************************************************************/
        for(i=0; i<4; ++i)
        {
            PlayerEndRound(arr[i]);
        }
        TrickDestroy(trick);
        ++numOfTricks;
    }
    for(i=0; i<4; ++i)
    {
        PlayerDestroy(arr[i]);
    }
    DestroyDeck(deck);
END_UNIT

/********************************************/

TEST_SUITE(Trick Module Tests)

    TEST(Trick_Create_Null_Test)
    TEST(Trick_Create_Normal_Test)
    TEST(Trick_Double_Destroy_Test)
    TEST(Run_Trick_Test)
    TEST(Run_Few_Trics_Test)
    TEST(Run_13_Trics_Test)
END_SUITE