#include "player.h"
#include "vector.h"
#include <stdlib.h>
#include "card.h"
#include "deck.h"
#include "player.h"
#include "mu_test.h"
#include <stdio.h>
#include <string.h>

/********************************************/
UNIT(Player_Create_Test)
    Player *player = NULL;
    const char* str = NULL;
    player = PlayerCreate("Adham", 0);
    ASSERT_THAT(NULL != player);
    str = PlayerGetName(player);
    ASSERT_THAT(strcmp(str,"Adham") == 0);
    PlayerDestroy(player);
END_UNIT
/********************************************/
UNIT(Player_Double_Destroy_Test)
    Player *player = NULL;
    const char *str = NULL;
    player = PlayerCreate("Adham", 0);
    ASSERT_THAT(NULL != player);
    str = PlayerGetName(player);
    ASSERT_THAT(strcmp(str, "Adham") == 0);
    PlayerDestroy(player);
    PlayerDestroy(player);
END_UNIT
/********************************************/
UNIT(player_Insert_One_Card_Test)
    int card;
    Player* player = NULL;
    Deck* deck;
    deck = CreateDeck();
    player = PlayerCreate("Adham", 0);
    ASSERT_THAT(NULL != player);
    ShuffleCards(deck);
    card =  DealCard(deck);
    ASSERT_THAT (PlayerInitRound(player, deck) == ERR_OK);
    ASSERT_THAT (PlayerInsertCard(player, card) == ERR_OK);
    ASSERT_THAT(PlayerEndRound(player) == ERR_OK);
    DestroyDeck(deck);
    PlayerDestroy(player);
END_UNIT
/********************************************/

UNIT(player_Insert_Few_Cards_Test)
    int card, i;
    Player* player = NULL;
    Deck* deck;
    deck = CreateDeck();
    player = PlayerCreate("Adham", 0);
    ASSERT_THAT(NULL != player);
    ShuffleCards(deck);
    ASSERT_THAT(PlayerInitRound(player, deck) == ERR_OK);
    for(i = 0; i < 5; ++i)
    {
        card =  DealCard(deck);
        ASSERT_THAT (PlayerInsertCard(player, card) == ERR_OK);
    }
    ASSERT_THAT(PlayerEndRound(player) == ERR_OK);
    DestroyDeck(deck);
    PlayerDestroy(player);
END_UNIT

UNIT(player_Insert_13_Cards_Test)
    int card, i;
    Player* player = NULL;
    Deck* deck;
    deck = CreateDeck();
    player = PlayerCreate("Adham", 0);
    ASSERT_THAT(NULL != player);
    ShuffleCards(deck);
    ASSERT_THAT(PlayerInitRound(player, deck) == ERR_OK);
    for(i = 0; i < 13; ++i)
    {
        card =  DealCard(deck);
        ASSERT_THAT (PlayerInsertCard(player, card) == ERR_OK);
    }
    ASSERT_THAT(PlayerEndRound(player) == ERR_OK);
    DestroyDeck(deck);
    PlayerDestroy(player);
END_UNIT

UNIT(Player_Play_One_Card_Test)
    int card, i;
    size_t	_numOfItems;
    Vector* _table = NULL;
    Player* player = NULL;
    Deck* deck;
    deck = CreateDeck();
    player = PlayerCreate("Adham", 0);
    _table = VectorCreate(4,0);
    VectorAdd(_table,  13); 
    ASSERT_THAT(NULL != player);
    ShuffleCards(deck);
    ASSERT_THAT(PlayerInitRound(player, deck) == ERR_OK);
    for(i = 0; i < 13; ++i)
    {
        card =  DealCard(deck);
        ASSERT_THAT (PlayerInsertCard(player, card) == ERR_OK);
    }
    PlayerPlay(player, _table);
    VectorItemsNum(_table, &_numOfItems);
    ASSERT_THAT(_numOfItems == 2);
    VectorDestroy(_table);
    ASSERT_THAT(PlayerEndRound(player) == ERR_OK);
    DestroyDeck(deck);
    PlayerDestroy(player);
END_UNIT

UNIT(Player_Play_13_Cards_Test)
    int card, i, del;
    size_t	_numOfItems;
    Vector* _table = NULL;
    Player* player = NULL;
    Deck* deck;
    deck = CreateDeck();
    player = PlayerCreate("Adham", 0);
    _table = VectorCreate(4,0);
    VectorAdd(_table,  13); 
    ASSERT_THAT(NULL != player);
    ShuffleCards(deck);
    ASSERT_THAT(PlayerInitRound(player, deck) == ERR_OK);
    for(i = 0; i < 13; ++i)
    {
        card =  DealCard(deck);
        ASSERT_THAT (PlayerInsertCard(player, card) == ERR_OK);
    }

    for(i =0; i<13; ++i)
    {
        ASSERT_THAT(PlayerPlay(player, _table) == ERR_OK);
        VectorItemsNum(_table, &_numOfItems);
        /*ASSERT_THAT(_numOfItems == 2);*/
        VectorDelete(_table, &del);
    }
    VectorDestroy(_table);
    ASSERT_THAT(PlayerEndRound(player) == ERR_OK);
    DestroyDeck(deck);
    PlayerDestroy(player);
END_UNIT


TEST_SUITE(Player Module Tests)
    TEST(Player_Create_Test)
    TEST(Player_Double_Destroy_Test)
    TEST(player_Insert_One_Card_Test)
    TEST(player_Insert_Few_Cards_Test)
    TEST(player_Insert_13_Cards_Test)
    TEST(Player_Play_One_Card_Test)
    TEST(Player_Play_13_Cards_Test)
END_SUITE