#ifndef _BITWISE_H_
#define _BITWISE_H_

#include <stdlib.h> /*for sizet*/
#include <stdio.h>
#define BUFFER 8

typedef struct BitMap BitMap;

/*******************************************************************************
*[Description]:Creates and allocates bitmap structure with afixed size 
*(Power of 2) char array.
*[Input]:bits number (size of the array) 
*[Return]:Pointer to Bitmap structure. NULL will return if bitsnumber equals zero
*Or Malloc fails to allocate memory.
*[Errors]:No errors return
*******************************************************************************/
BitMap* CreateBitMap(size_t _bitsNumber);

/*******************************************************************************
*[Description]:Deallocate the memory for the above structure and for char array
*[Input]:Adress of the Pointer to Bit Map structure.
*[return]:Void. (no return value)
*[Errors]:No errors return
*******************************************************************************/
void DestroyBitMap(BitMap **_bMPtr);

/*******************************************************************************
*[Description]:Turns the bit number ON. bit number givin by Caller. if the bit is
*Already ON - bit state will preserved. Caller responsible for valid bit number.
*[Input]:Bit number to Turn ON and pointer to Bitmap struct
*[return]: 0 will return in success situation and 1 will return in failure due to
*NULL BitMap Pointer Or Invalid Bit NUmber.
*[Errors]:1 will return in failure due to NULL BitMap Pointer Or Invalid Bit NUmber.
*******************************************************************************/
int TurnBitOn(size_t _bitNumber, BitMap* _bMPtr);

/*******************************************************************************
*[Description]:Turns the bit number OFF. bit number givin by Caller. if the bit is
*Already OFF - bit state will preserved. Caller responsible for valid bit number.
*[Input]:Bit number to Turn OFF and pointer to Bitmap struct
*[return]: 0 will return in success situation and 1 will return in failure due to
*NULL BitMap Pointer Or Invalid Bit NUmber.
*[Errors]:1 will return in failure due to NULL BitMap Pointer Or Invalid Bit NUmber.
*******************************************************************************/
int TurnBitOff(size_t _bitNumber, BitMap* _bMPtr);

/*******************************************************************************
*[Description]:Check if bit number Is ON. bit number givin by Caller. if the bit is
*ON - 1 will return, if the bit is OFF, 0 will return. 
*Caller responsible for valid bit number.
*[Input]:Bit number to Turn CHECK and pointer to Bitmap struct
*[return]: 0 will return in OFF bit state and 1 will return in ON state. -1 will
*be return due to NULL BitMap Pointer Or Invalid Bit NUmber.
*[Errors]:-1 will return in failure due to NULL BitMap Pointer Or Invalid Bit NUmber.
*******************************************************************************/
int IsBitOn(size_t _bitNumber, BitMap* _bMPtr);

/*******************************************************************************
*[Description]:Function for Operating bits functions.
*[Input]:Function Pointer (to one of the above functions), bit number and Pointer
*to bit map struct.
*nedded 
*[output]:Functionality will returned acording to function pointer value
*[Errors]:0 - means success 1 means failure
*******************************************************************************/
//int Operate(bitz t, size_t bit, BitMap *_bMPtr);

/*Display binary bits in aspecefic Byte in bits array*/
int DisplayBits(size_t _byteNum, BitMap *_bMPtr);

#endif /*_BITWISE_H_*/
