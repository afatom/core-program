#include "deck.h"
#include "card.h"
#include <stdlib.h>     /*malloc*/
#include "vector.h"     /*Cards index container*/
#include <time.h>       /*srand*/
#include <stdio.h>		/*printing*/

#define DECK_MAGIC 963258741
#define DECK_NUM_OF_CARDS 52

struct Deck {
    size_t  m_magicNumber;
    Card    m_cards[DECK_NUM_OF_CARDS];
    Vector* m_shuffled;
};

Card cards[DECK_NUM_OF_CARDS] =
    {
        {HEARTS, RANK_2},
        {HEARTS, RANK_3},
        {HEARTS, RANK_4},
        {HEARTS, RANK_5},
        {HEARTS, RANK_6},
        {HEARTS, RANK_7},
        {HEARTS, RANK_8},
        {HEARTS, RANK_9},
        {HEARTS, RANK_10},
        {HEARTS, RANK_JACK},
        {HEARTS, RANK_QUEEN},
        {HEARTS, RANK_KING},
        {HEARTS, RANK_ACE},

        {CLUBS, RANK_2},
        {CLUBS, RANK_3},
        {CLUBS, RANK_4},
        {CLUBS, RANK_5},
        {CLUBS, RANK_6},
        {CLUBS, RANK_7},
        {CLUBS, RANK_8},
        {CLUBS, RANK_9},
        {CLUBS, RANK_10},
        {CLUBS, RANK_JACK},
        {CLUBS, RANK_QUEEN},
        {CLUBS, RANK_KING},
        {CLUBS, RANK_ACE},

        {DIAMOND, RANK_2},
        {DIAMOND, RANK_3},
        {DIAMOND, RANK_4},
        {DIAMOND, RANK_5},
        {DIAMOND, RANK_6},
        {DIAMOND, RANK_7},
        {DIAMOND, RANK_8},
        {DIAMOND, RANK_9},
        {DIAMOND, RANK_10},
        {DIAMOND, RANK_JACK},
        {DIAMOND, RANK_QUEEN},
        {DIAMOND, RANK_KING},
        {DIAMOND, RANK_ACE},

        {SPADES, RANK_2},
        {SPADES, RANK_3},
        {SPADES, RANK_4},
        {SPADES, RANK_5},
        {SPADES, RANK_6},
        {SPADES, RANK_7},
        {SPADES, RANK_8},
        {SPADES, RANK_9},
        {SPADES, RANK_10},
        {SPADES, RANK_JACK},
        {SPADES, RANK_QUEEN},
        {SPADES, RANK_KING},
        {SPADES, RANK_ACE}

};

/*****************************************************************************/
static void swap(Vector *_vec, size_t _firstIndex, size_t _secIndex);
static void ShuffleVector(Deck* _deck, int _size);
/*****************************************************************************/
Deck* CreateDeck(void)
{

    int i;
    Deck* deck = NULL;
    srand((unsigned int)time(NULL));
    deck = (Deck*)malloc(sizeof(Deck));
    if(NULL == deck)
    {
        return NULL;
    }
    deck->m_shuffled = VectorCreate(DECK_NUM_OF_CARDS, 0);
    if(NULL == deck->m_shuffled)
    {
        free(deck);
        return NULL;
    }
    deck->m_magicNumber = DECK_MAGIC;
   /* deck->m_cards = &cards;*/

    for (i = 0; i < DECK_NUM_OF_CARDS; ++i)
    {
        deck->m_cards[i]= cards[i];
    }

    return deck;
}
/*****************************************************************************/
void DestroyDeck(Deck* _deck)
{
    if(NULL == _deck || _deck->m_magicNumber == 0)
    {
        return;
    }
    _deck->m_magicNumber = 0;
    free(_deck->m_shuffled);
    /*free(_deck->m_cards);*/
    free(_deck);
}
/*****************************************************************************/
void ShuffleCards(Deck* _deck)
{
    int i;
    if(NULL == _deck)
    {
        return;
    }
    /*add elements to vector*/
    for (i = 0; i < DECK_NUM_OF_CARDS; ++i)
    {
        VectorAdd(_deck->m_shuffled, i);
    }
    /*shuffle vector elements*/
    ShuffleVector(_deck, DECK_NUM_OF_CARDS);
    /*VectorPrint(_deck->m_shuffled);*/
}
/*****************************************************************************/
int DealCard(Deck *_deck)
{
    int card;
    if(NULL == _deck)
    {
        return -1;
    }
    VectorDelete(_deck->m_shuffled, &card);
    return card;
}
/*****************************************************************************/
const Card* GetCard(int _cardIndex, Deck* _deck)
{
    if(NULL == _deck || ((_cardIndex < 0 || _cardIndex > DECK_NUM_OF_CARDS-1)))
    {
        return NULL;
    }
    return &(cards[_cardIndex]);
    /*return &([_cardIndex]);*/
}

const int GetCardIndex(Card *_card, Deck *_deck)
{
    int i=-1;
    if(NULL == _card || NULL == _deck)
    {
        return -1;
    }
    for(i =0; i<52; ++i)
    {
        if ((*_card).suit == _deck->m_cards[i].suit  && (*_card).rank == _deck->m_cards[i].rank )
        {
            return i;
        }
    }
    return -1;
}

void PrintCard(const Card* _card)
{

    if(_card->suit == HEARTS)
    {
        puts("Suit: HEARTS");
    }
    else if (_card->suit == DIAMOND)
    {
        puts("Suit: DIAMOND");
    }
    else if (_card->suit == SPADES)
    {
        puts("Suit: SPADES");
    }
    else{
        puts("Suit: CLUBS");
    }

    switch (_card->rank)
    {
        case RANK_2:
        puts("Rank 2"); break;
        case RANK_3:
        puts("Rank 3"); break;
        case RANK_4:
        puts("Rank 4"); break;
        case RANK_5:
        puts("Rank 5"); break;

        case RANK_6:
        puts("Rank 6"); break;
        case RANK_7:
        puts("Rank 7"); break;
        case RANK_8:
        puts("Rank 8"); break;
        case RANK_9:
        puts("Rank 9"); break;

        case RANK_10:
        puts("Rank 10"); break;
        case RANK_JACK:
        puts("Rank JACK"); break;
        case RANK_QUEEN:
        puts("Rank QUEEN"); break;
        case RANK_KING:
        puts("Rank KING"); break;
        case RANK_ACE:
        puts("Rank ACE"); break;
        default: break;

    }

}

/*****************************************************************************/

/****************************/
/*     Static Functions     */
/****************************/
/*****************************************************************************/
static void swap(Vector *_vec, size_t _firstIndex, size_t _secIndex)
{
    int firstVal, secVal;
    VectorGet(_vec, _firstIndex, &firstVal);
    VectorGet(_vec, _secIndex, &secVal);
    VectorSet(_vec, _secIndex, firstVal);
    VectorSet(_vec, _firstIndex, secVal);
}
/*****************************************************************************/
static void ShuffleVector(Deck* _deck, int _size)
{
    int i, newIndex;
    /*srand(time(NULL));*/
    /*
    VectorPrint(_deck->m_shuffled);*/
    /*Start from the last element and swap one by one. We don't
    need to run for the first element that's why i > 0*/
    for (i = _size -1; i >= 0; --i)
    {
        /*Choose random index from 0 to i*/
        /*Optional - %size*/
        newIndex = rand() % (i+1);
        /*Swap Vector[i] with the element at random index*/
        swap(_deck->m_shuffled, (size_t)i, (size_t)newIndex);
    }
    /*
    VectorPrint(_deck->m_shuffled);*/
    /*
    InsertionSort(_deck->m_shuffled);
    VectorPrint(_deck->m_shuffled);*/
}
