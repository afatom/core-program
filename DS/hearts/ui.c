
#include "ui.h"
#include "vector.h"
#include "deck.h"
#include "card.h"
#include <stdio.h>
#include <stdlib.h>


/***********************************/
/* bold - not bold */
#define BOLD_ON         "\x1b[1m"
#define BOLD_OFF        "\x1b[21m"
/***********************************/
/* colors */
#define NORMAL          "\x1B[0m"
#define BLACK           "\x1b[30m"
#define RED             "\x1B[31m"
#define GREEN           "\x1B[32m"
#define YELLOW          "\x1B[33m"
#define BLUE            "\x1B[34m"
#define MAGENTA         "\x1B[35m"
#define CYAN            "\x1B[36m"
#define WHITE           "\x1B[37m"
#define GRAY            "\x1b[90m"
/***********************************/
/* cards suites symbols */
#define _HEART_           "\xE2\x99\xA5"
#define _SPADE_           "\xE2\x99\xA0"
#define _DIAMOND_         "\xE2\x99\xA6"
#define _CLUB_            "\xE2\x99\xA3"

/***********************************/

void PrintColoredCard(const Card* _card);
void PrintPlayerCards(Vector** cards, const char* playerName, Deck* _deck);
int GetHumanCard(Deck *_deck);
void PrintTable(Vector *_table, Deck *_deck);
void GetString(const char *msg, char *str);
void PutString(const char *msg);

void GetString(const char *msg, char *str)
{
    /*char str[32]="a";*/
    printf("\n%s\n",msg);
    fflush(stdin);
    scanf("\n%s\n", str);
   
}

void GetPlayerName(const char *msg, char *str, int _maxNameLength)
{
    /*char str[32]="a";*/
    printf("\n%s\n", msg);
    fflush(stdin);
    fgets(str,_maxNameLength,stdin);
    /*scanf("\n%s\n", str);*/
  
}

void PutString(const char *msg)
{
    /*fflush(stdin);*/
    printf(GREEN "%s\n" NORMAL, msg);
}



void PrintTable(Vector *_table, Deck *_deck)
{
    
    int cardIndex=0;
    size_t j, noi =0;

    /*fflush(stdin);*/
    VectorItemsNum(_table, &noi);
    if(noi == 0)
    {
        puts(" Empty Table ");
    }
    for(j = 0; j < noi; ++j)
    {
        VectorGet(_table, j, &cardIndex);
        PrintColoredCard(GetCard( cardIndex, _deck));
    }
    
}

void Print3Cards(int *arr, Deck *_deck)
{
   
    int j;

    /*fflush(stdin);*/
    for (j = 0; j < 3; ++j)
    {
        PrintColoredCard(GetCard((arr[j]), _deck));
    }
    puts("\n");
}


void PrintPlayerCards(Vector** cards, const char* playerName, Deck* _deck)
{
    
    int cardIndex;
    size_t i, j, noi =0;

    fflush(stdin);
    printf("%s\n", playerName);
    for(i = 0; i < 4; ++i)
    {
        noi =0;
        VectorItemsNum(cards[i],&noi);
        for(j = 0; j < noi; ++j)
        {
            VectorGet(cards[i], j,&cardIndex);
            PrintColoredCard(GetCard( cardIndex, _deck));
        }
    }
    puts("\n");
}

void PrintHandCards(Vector** cards, Deck* _deck)
{
 
    int cardIndex;
    size_t i, j, noi =0;

    fflush(stdin);
    printf("\n---------------------------------------------------------------------------------\n");
    for(i = 0; i < 4; ++i)
    {
        noi =0;
        VectorItemsNum(cards[i],&noi);
        for(j = 0; j < noi; ++j)
        {
            VectorGet(cards[i], j,&cardIndex);
            PrintColoredCard(GetCard( cardIndex, _deck));
        }
    }
    printf("\n---------------------------------------------------------------------------------\n");
}


int GetHumanCard(Deck *_deck)
{
    int input=0;
    char card[6];
    Card humanCard;
    
    fflush(stdin); /*make sure no garbage in stdin buffer*/
   
    do
    {
        
        printf("Throw Card leading with the suit(@ upper case letters only)\n");

        fgets(card, 5, stdin);
        switch (card[0])
        {
        case 'H':
                humanCard.suit = HEARTS;
                break;

            case 'D':
                humanCard.suit = DIAMOND;
                break;

            case 'S':
                humanCard.suit = SPADES;
                break;

            case 'C':
                humanCard.suit = CLUBS;
                break;
            default:
                
                break;
        }

        switch(card[1])
        {
        case '2':
            humanCard.rank=RANK_2; 
            break;
            case '3':
                humanCard.rank = RANK_3;
                break;
            case '4':
                humanCard.rank = RANK_4;
                break;
            case '5':
                humanCard.rank = RANK_5;
                break;

            case '6':
                humanCard.rank = RANK_6;
                break;
            case '7':
                humanCard.rank = RANK_7;
                break;
            case '8':
                humanCard.rank = RANK_8;
                break;
            case '9':
                humanCard.rank = RANK_9;
                break;

            case 'J':
                humanCard.rank = RANK_JACK;
                break;
            case 'Q':
                humanCard.rank = RANK_QUEEN;
                break;
            case 'K':
                humanCard.rank = RANK_KING;
                break;
            case 'A':
                humanCard.rank = RANK_ACE;
                break;
            default:
                humanCard.rank = RANK_10;
                break;
        }

        input = GetCardIndex(&humanCard, _deck);
        if(input < 0)
        {
            puts("Envalid Suit Input");
        }
    } while(input < 0);
    return input;
}


/***************************************************************************/
void PrintColoredCard(const Card* _card)
{

    /*fflush(stdin);*/

    switch (((Card*)_card)->rank)
    {
        case RANK_2:
        printf(" 2 " ); break;
        case RANK_3:
        printf( " 3 " ); break;
        case RANK_4:
        printf( " 4 " ); break;
        case RANK_5:
        printf( " 5 " ); break;

        case RANK_6:
        printf( " 6 " ); break;
        case RANK_7:
        printf( " 7 " ); break;
        case RANK_8:
        printf( " 8 " ); break;
        case RANK_9:
        printf( " 9 " ); break;

        case RANK_10:
        printf( " 10 " ); break;
        case RANK_JACK:
        printf( " J " ); break;
        case RANK_QUEEN:
        printf( " Q " ); break;
        case RANK_KING:
        printf( " K " ); break;
        case RANK_ACE:
        printf( " A "); break;
        default: break;

    }
    if (((Card *)_card)->suit == HEARTS)
    {
        printf(RED _HEART_ NORMAL);
        
    }
    else if (((Card *)_card)->suit == DIAMOND)
    {
        printf(RED _DIAMOND_ NORMAL);
        
    }
    else if (((Card *)_card)->suit == SPADES)
    {
        printf(WHITE _SPADE_ NORMAL);
        
    }
    else
    {
        printf(WHITE _CLUB_ NORMAL);
       
    }
    printf("  ");

}

void PrintPlayerScore(const char* _playerName , size_t _score)
{
    fflush(stdin);
    printf("The Looser Player Is -->> :: %s :: His Score -->> :: %lu ::\n", _playerName, _score);
}
