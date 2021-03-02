#ifndef _DECK_H_
#define _DECK_H_

#include "card.h"

typedef struct Deck Deck;

/*******************************************************************************
*[Description]:Creating Deck module. Round will create deck and will destroy it 
*also. this module includes the 52 cards and the shuffled vector also.  
*[Inputs]:Void
*[return]:Deck pointer.
*[Errors]:No errors return. NULL will return if there was error while alocating 
*vector.
*******************************************************************************/
Deck* CreateDeck(void);
/*******************************************************************************
*[Description]:Destroying Deck module and freeing allocating vector. this function
*take care in double freeing case.
*[Inputs]:deck pointer
*[return]:void
*[Errors]:No errors return.
*******************************************************************************/
void DestroyDeck(Deck* _deck);

/*******************************************************************************
*[Description]:Dealing card! one card in random way from the deck. deck need to be
*shuffled before dealing acard. dealed card obtained as an index. this index should
*be translatten in get card function. 
*[Inputs]:Deck pointer
*[return]:Index of the the dealed card.
*[Errors]:No errors return.
*******************************************************************************/
int DealCard(Deck *_deck);
/*******************************************************************************
*[Description]:Fill the vector with ascending number 0-55. and then shuffles it. 
*[Inputs]:void
*[return]:Void
*[Errors]:No errors return.
*******************************************************************************/
void ShuffleCards(Deck* _deck);
/*******************************************************************************
*[Description]:Fill the vector with ascending number 0-51. and then shuffles it. 
*[Inputs]:index number wich need to be converted to Card terms.
*[return]:Card pointer (Pointer for propprate card wich suitable to index number)
*[Errors]:No errors return.
*******************************************************************************/
const Card* GetCard(int _cardIndex, Deck* _deck);

const int GetCardIndex(Card* _card, Deck* _deck);

/*UNIT test only*/
void PrintCard(const Card* _card);

#endif /* _DECK_H_*/