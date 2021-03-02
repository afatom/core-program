#include "bitwise.h"
#include <stdlib.h>
#include <stdio.h>

#define BUFFER 8

struct BitMap {
    char* m_bits;
    size_t   m_numberOfBits;   
};


/*******************************************************************/
BitMap* CreateBitMap(size_t _bitsNumber)
{
    BitMap* _bMPtr = NULL;
    size_t fixedSize, resdue;
    if (_bitsNumber == 0)
    {
        return NULL;
    }
    resdue = _bitsNumber % BUFFER;
    if (resdue == 0)
    {
        fixedSize = _bitsNumber;
    }
    else
    {
        fixedSize = _bitsNumber + (BUFFER - resdue);
    }
    _bMPtr = (BitMap*)malloc(sizeof(BitMap));
    if (NULL == _bMPtr)
    {
        return NULL;
    }
    (_bMPtr->m_bits) = (char*)calloc((fixedSize/BUFFER), sizeof(char));
    if (NULL == _bMPtr->m_bits)
    {
        free(_bMPtr);
        return NULL;
    }
    _bMPtr->m_numberOfBits = _bitsNumber;
    return _bMPtr;
}
/*******************************************************************/
void DestroyBitMap(BitMap **_bMPtr)
{
    if(*_bMPtr == NULL)
    {
        return;
    }
    free((*_bMPtr)->m_bits);
    free(*_bMPtr);
    *_bMPtr = NULL;
    return;
}
/*******************************************************************/
int DisplayBits(size_t _byteNum, BitMap *_bMPtr)
{ 
	int i=BUFFER-1;
    unsigned char res = _bMPtr->m_bits[_byteNum];
    int arr[BUFFER]={0};
    while(i >=0)
    {
        arr[i] = (res % 2);   
        res = res/2;
        --i;
    }
    printf("***************\n");
    for(i=0; i< BUFFER; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n***************\n");
    return 0;
}
/*******************************************************************/
static int CheckParameters(size_t _bitNumber, BitMap *_bMPtr)
{
    if (_bMPtr == NULL)
    {
        return 1;
    }
    if (_bitNumber > _bMPtr->m_numberOfBits)
    {
        return 1; /*invalid inputs*/
    }
    return 0; /*valid inputs*/
} 

/*******************************************************************/
int TurnBitOn(size_t _bitNumber, BitMap *_bMPtr)
{
    size_t ByteNumber, bitInByte, i=1, c;
    if (CheckParameters(_bitNumber, _bMPtr))
    {
        return 1; /*invalid inputs*/
    }
    
    ByteNumber = _bitNumber / BUFFER;
    bitInByte = _bitNumber % BUFFER;
    i<<=bitInByte;
    _bMPtr->m_bits[ByteNumber] = (_bMPtr->m_bits[ByteNumber])|i;
    return 0;
}
/*******************************************************************/
int TurnBitOff(size_t _bitNumber, BitMap* _bMPtr)
{
    size_t ByteNumber, bitInByte, i=1, c;
    if (CheckParameters(_bitNumber, _bMPtr))
    {
        return 1; /*invalid inputs*/
    }

    ByteNumber = _bitNumber/BUFFER;
    bitInByte = _bitNumber % BUFFER;
    i<<=bitInByte;
    i=~i; /*NOT(i)*/
    _bMPtr->m_bits[ByteNumber] = (_bMPtr->m_bits[ByteNumber])&i;
    return 0;
}

/*******************************************************************/
int IsBitOn(size_t _bitNumber, BitMap* _bMPtr)
{
   
    size_t ByteNumber, bitInByte; 
    int i=1; 
    int c;
    if (CheckParameters(_bitNumber, _bMPtr))
    {
        return 1; /*invalid inputs*/
    }
    ByteNumber = _bitNumber/BUFFER; /*array index*/
    bitInByte = _bitNumber % BUFFER;
    c = _bMPtr->m_bits[ByteNumber];
    i<<=bitInByte;
    i = c&i;
    if (i == 0)
    {
        return 0; /*bit off*/
    }
    return 1;
}
/*******************************************************************/

