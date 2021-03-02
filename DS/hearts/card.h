#ifndef _CARD_H_
#define _CARD_H_

#define ENUM_BIAS 0
/*****************************************************************************/
/*Card.h Is just an enum file. and must to be included in every c file or h 
**file that uses Card enum data type.
******************************************************************************/

/***************************** Suit enum*/
typedef enum {
    HEARTS = 0,
    CLUBS,
    SPADES,
    DIAMOND
}Suit;
/*******************************Rank enum*/
typedef enum {
    /*RANK_2 = 0,*/ /*<<Bug H2 appears than once*/
    RANK_2 = ENUM_BIAS, /*<< Bug fixed*/
    RANK_3,
    RANK_4,
    RANK_5,
    RANK_6,
    RANK_7,
    RANK_8,
    RANK_9,
    RANK_10,
    RANK_JACK,
    RANK_QUEEN,
    RANK_KING,
    RANK_ACE
}Rank;
/*******************************************/
typedef struct Card {
    Suit suit;
    Rank rank;
}Card;
/*******************************************/

#endif /*_CARD_H_*/