#include "vector.h"
#include "deck.h"
#include "card.h"
#include <stdio.h>
#include "ui.h"





int main ()
{
    int i;
    Deck* deck =  CreateDeck( );
    ShuffleCards(deck);
    for(i=0; i<52; ++i)
    {
        PrintColoredCard(GetCard(DealCard(deck), deck));
    }
    DestroyDeck(deck);
    
    return 0;
}