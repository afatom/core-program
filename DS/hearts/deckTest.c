#include <stdlib.h>
#include "card.h"
#include "deck.h"
#include "mu_test.h"
#include <stdio.h>
#include <string.h>

static int FindMax(int* arr,int size)
{
    int i;
    int max = arr[0];
    for(i = 0; i< size; ++i)
    {
        if(arr[i] > max)
        {
            max = arr[i];
        }
    }
    return max;
}


/********************************************/
UNIT(Deck_Create_Deck_Test)
Deck *deck = NULL;
deck = CreateDeck();
ASSERT_THAT(NULL != deck);
DestroyDeck(deck);
END_UNIT
/********************************************/
UNIT(Deck_Double_Destroy_Test)
Deck *deckk = NULL;
deckk = CreateDeck();
ASSERT_THAT(NULL != deckk);
DestroyDeck(deckk);
/*DestroyDeck(deckk);*/
END_UNIT
/********************************************/
UNIT(Shuffle_Cards_Normal_Test)
    Deck *deckk = NULL;
    deckk = CreateDeck();
    ASSERT_THAT(NULL != deckk);
    ShuffleCards(deckk);
    DestroyDeck(deckk);
END_UNIT
/********************************************/
UNIT(Deal_ALL_Cards_Test)
    int arr [52]={0}, i,j,k;
    int arrc[52]={0};
    int max;
    Deck *deckk = NULL;
    deckk = CreateDeck();
    ASSERT_THAT(NULL != deckk);
    ShuffleCards(deckk);
    for(k=0; k<1; ++k)
    {
        for(i =0; i < 52; ++i)
        {
            arr[i]=DealCard(deckk);

        }
        max =  FindMax(arr, 52);
        /*
        arrc =  (int*)calloc((size_t)max,sizeof(int));*/
        for(j =0; j <= max; ++j)
        {
            ++arrc[arr[j]];
        }
        for (j = 0; j <= max; ++j)
        {
            ASSERT_THAT(arrc[j]==1);
        }
        for (j = 0; j <= max; ++j)
        {
            ASSERT_THAT(arrc[j]==1);
        }
        memset(arrc, 0, 52);
    }
    /*free(arrc);*/
    DestroyDeck(deckk);
END_UNIT
/********************************************/
TEST_SUITE(Deck Module Tests)
    TEST(Deck_Create_Deck_Test)
    TEST(Deck_Double_Destroy_Test)
    TEST(Deal_ALL_Cards_Test)
END_SUITE
