#include "hand.h"
#include "vector.h"
#include <stdlib.h>
#include "card.h"
#include "deck.h"
#include "mu_test.h"
#include <stdio.h>

/********************************************/
UNIT(Hand_Create_Deck_Null_Test)
    Hand* hand = NULL;
    Deck* deck = NULL;
    hand = HandCreate(deck);
    ASSERT_THAT(NULL == hand);
END_UNIT
/********************************************/
UNIT(Hand_Create_Normal_Test)
    Hand* hand = NULL;
    Deck* deck;
    deck = CreateDeck();
    hand = HandCreate(deck);
    ASSERT_THAT(NULL != hand);
    DestroyDeck(deck);
    HandDestroy(hand);
END_UNIT
/********************************************/
UNIT(Hand_Destroy_Normal_Test)
    Hand* hand = NULL;
    Deck* deck;
    deck = CreateDeck();
    hand = HandCreate(deck);
    ASSERT_THAT(NULL != hand);
    DestroyDeck(deck);
    HandDestroy(hand);
END_UNIT
/********************************************/
UNIT(Hand_Double_Destroy_Test)
    Hand* hand = NULL;
    Deck* deck;
    deck = CreateDeck();
    hand = HandCreate(deck);
    ASSERT_THAT(NULL != hand);
    DestroyDeck(deck);
    HandDestroy(hand);
    HandDestroy(hand);
END_UNIT
/********************************************/
UNIT(Hand_Insert_One_Card_Test)
    int card;
    Hand* hand = NULL;
    Deck* deck;
    deck = CreateDeck();
    hand = HandCreate(deck);
    ASSERT_THAT(NULL != hand);
    ShuffleCards(deck);
    card =  DealCard(deck);
    ASSERT_THAT (HandInsertCard(hand, card) == ERR_OK);
    /*
    mcard = GetCard(card, deck);
    PrintCard(mcard);
    HandPrintCards(hand);
    */
    DestroyDeck(deck);
    HandDestroy(hand);
END_UNIT
/********************************************/
UNIT(Hand_Insert_Few_Cards_Test)
    int card, i;
    Hand* hand = NULL;
    Deck* deck;
    deck = CreateDeck();
    hand = HandCreate(deck);
    ASSERT_THAT(NULL != hand);
    ShuffleCards(deck);
    for(i = 0; i < 5; ++i)
    {
        card =  DealCard(deck);
        ASSERT_THAT (HandInsertCard(hand, card) == ERR_OK);
    }
    DestroyDeck(deck);
    HandDestroy(hand);
END_UNIT
/********************************************/
UNIT(Hand_Insert_13_Cards_Test)
    int card, i;
    Hand* hand = NULL;
    Deck* deck;
    deck = CreateDeck();
    hand = HandCreate(deck);
    ASSERT_THAT(NULL != hand);
    ShuffleCards(deck);
    for(i = 0; i < 13; ++i)
    {
        card =  DealCard(deck);
        ASSERT_THAT (HandInsertCard(hand, card) == ERR_OK);
    }
    DestroyDeck(deck);
    HandDestroy(hand);
END_UNIT
/********************************************/
UNIT(Hand_Play_One_Card_Test)
    int card, i;
    size_t	_numOfItems;
    Vector* _table = NULL;
    Hand* hand = NULL;
    Deck* deck;
    deck = CreateDeck();
    hand = HandCreate(deck);
    _table = VectorCreate(4,0);
    VectorAdd(_table,  13); 
    ASSERT_THAT(NULL != hand);
    ShuffleCards(deck);
    for(i = 0; i < 13; ++i)
    {
        card =  DealCard(deck);
        ASSERT_THAT (HandInsertCard(hand, card) == ERR_OK);
    }
    HandPlay(hand, _table);
    VectorItemsNum(_table, &_numOfItems);
    ASSERT_THAT(_numOfItems == 2);
    VectorDestroy(_table);
    DestroyDeck(deck);
    HandDestroy(hand);
END_UNIT
/********************************************/
UNIT(Hand_Play_13_Cards_Test)
    int card, i;
    size_t	_numOfItems;
    Vector* _table = NULL;
    Hand* hand = NULL;
    Deck* deck;
    deck = CreateDeck();
    hand = HandCreate(deck);
    _table = VectorCreate(15,0);
    VectorAdd(_table, 25);
    ASSERT_THAT(NULL != hand);
    ShuffleCards(deck);
    for(i = 0; i < 13; ++i)
    {
        card =  DealCard(deck);
        ASSERT_THAT (HandInsertCard(hand, card) == ERR_OK);
    }

    for(i = 0; i<13; ++i)
    {
        ASSERT_THAT(HandPlay(hand, _table) == ERR_OK);
        VectorItemsNum(_table, &_numOfItems);
        ASSERT_THAT(_numOfItems == i+2);
        
    }
    VectorDestroy(_table);
    DestroyDeck(deck);
    HandDestroy(hand);
END_UNIT
/********************************************/
UNIT(Hand_ADD_Points_Test)
    
END_UNIT
/********************************************/
UNIT(Hand_Get_Round_Points_Test)
    
END_UNIT
/********************************************/

TEST_SUITE(Hand Module Tests)
    TEST(Hand_Create_Deck_Null_Test)
    TEST(Hand_Create_Normal_Test)
    TEST(Hand_Destroy_Normal_Test)
    TEST(Hand_Double_Destroy_Test)
    TEST(Hand_Insert_One_Card_Test)
    TEST(Hand_Insert_Few_Cards_Test)
    TEST(Hand_Insert_13_Cards_Test)
    TEST(Hand_Play_One_Card_Test)
    TEST(Hand_Play_13_Cards_Test)
END_SUITE