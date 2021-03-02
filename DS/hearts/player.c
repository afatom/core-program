#include "player.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "hand.h"
#include "vector.h"
#include "hand.h"
#include <stdio.h>

#define HUMAN_PLAYER 1
#define Computer_PLAYER  0

#define MAGIC 987456321
struct Player{
    size_t      m_playerMagicNumber;
    Hand*       m_hand;
    size_t      m_handMagicNumber;
    char        m_name[32]; 
    int         m_type;
    size_t      m_tottalScore;
    size_t      m_roundScore;
    
};

/*******************************************************************************/
Player* PlayerCreate(const char* _playerName, int _playerType)
{
    Player* playerPtr = NULL;
    playerPtr = (Player*)malloc(sizeof(Player));
    if(NULL == playerPtr)
    {
        return NULL;
    }
    playerPtr->m_playerMagicNumber = MAGIC;
    playerPtr->m_hand = NULL;
    playerPtr->m_handMagicNumber = MAGIC;
    strcpy(playerPtr->m_name, _playerName);/*---------------------------> BUG */
    /*playerPtr->m_name = _playerName;*/
    playerPtr->m_type = _playerType;
    playerPtr->m_tottalScore = 0;
    playerPtr->m_roundScore = 0;
    
    return playerPtr;
}
/*******************************************************************************/
void PlayerDestroy(Player *_player)
{
    if (NULL == _player || _player->m_playerMagicNumber == 0)
    {
        return;
    }
    _player->m_playerMagicNumber = 0;
    _player->m_hand = NULL;
    free(_player);
    _player = NULL;
}
/*******************************************************************************/
const char* PlayerGetName(Player* _player)
{
    if(NULL == _player)
    {
        return NULL;
    }
    return _player->m_name;
}
/*******************************************************************************/
ADTErr PlayerEndRound(Player *_player)
{
    size_t RoundPoints;
    if(NULL == _player || _player->m_hand == NULL)
    {
        return ERR_NOT_INITIALIZED;
    }
    if(_player->m_handMagicNumber == 0)
    {
        return ERR_OK;
    }
    /*get round score before destroying hand*/
    RoundPoints =  HandGetRoundPoints(_player->m_hand);
    _player->m_roundScore = RoundPoints;
    _player->m_tottalScore += RoundPoints;
    /*Destroy hand*/
    HandDestroy(_player->m_hand);
    _player->m_hand = NULL;
    return ERR_OK;
}
/*******************************************************************************/
int IsHumanPlayer(const Player *_player)
{
    if(NULL == _player || _player->m_type == HUMAN_PLAYER)
    {
        return HUMAN_PLAYER;
    }
    return Computer_PLAYER;
}
/*******************************************************************************/
size_t PlayerGetTottalPoints(Player* _player)
{
    if(NULL == _player)
    {
        return 0;
    }
    return _player->m_tottalScore; 
}
/*******************************************************************************/
size_t PlayerGetRoundPoints(Player* _player)
{
    if(NULL == _player)
    {
        return 0;
    }
    return _player->m_roundScore; 
}
/*******************************************************************************/
ADTErr PlayerAddTrickPoints(Player *_player, size_t _points)
{
    if(NULL == _player || _player->m_hand)
    {
        return ERR_NOT_INITIALIZED;
    }
    return HandAddTrickPoints(_player->m_hand, _points);
}
/*******************************************************************************/
int IsClubs2CardExistInMyHand(Player* _player)
{
    if(NULL == _player || NULL == _player->m_hand)
    {
        return ERR_NOT_INITIALIZED;
    }
    return IsClubs2CardExist(_player->m_hand);
}
/*******************************************************************************/
ADTErr PlayerPlay(Player *_player, Vector *_table, int _playerType)
{
    if(NULL == _player || NULL == _player->m_hand)
    {
        return ERR_NOT_INITIALIZED;
    }
    if(_table == NULL)
    {
        return ERR_INVALID_DATA_IN;
    }
    if(_player->m_type == HUMAN_PLAYER)
    {
        return HandPlay(_player->m_hand, _table, HUMAN_PLAYER);
    }
    return HandPlay(_player->m_hand, _table, Computer_PLAYER);
}
/*******************************************************************************/
ADTErr PlayerPassThreeCards(Player *_player, int *_cardsArr, int _playerType)
{
    if(NULL == _player || NULL == _player->m_hand)
    {
        return ERR_NOT_INITIALIZED;
    }
    if (_player->m_type == HUMAN_PLAYER)
    {
        return HandThrow3Cards(_player->m_hand, _cardsArr, HUMAN_PLAYER);
    }
    return HandThrow3Cards(_player->m_hand, _cardsArr, Computer_PLAYER);
}
/*******************************************************************************/
ADTErr PlayerInsertCard(Player* _player, int _cardIndex)
{
    if(NULL == _player || NULL == _player->m_hand)
    {
        return ERR_NOT_INITIALIZED;
    }
    return HandInsertCard(_player->m_hand, _cardIndex);
}
/*******************************************************************************/
ADTErr PlayerInitRound(Player* _player, Deck* _deck)
{
    Hand* hand = NULL;
    if(NULL == _player)
    {
        return ERR_NOT_INITIALIZED;
    }
    if(NULL == _deck)
    {
        return ERR_INVALID_DATA_IN;
    }
    /*Create hand*/
    hand = HandCreate(_deck);
    if(NULL == hand)
    {
        return ERR_ALLOCATION_FAILED;
    }
    _player->m_hand = hand;
    return ERR_OK;
}
/*******************************************************************************/


