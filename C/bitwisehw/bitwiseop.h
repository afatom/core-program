#ifndef _BITWISEOP_H_
#define _BITWISEOP_H_

#include <stdlib.h>

/*******************************************************************************
*[Description]:InvertBits, invert unsigned char x and return the answer in _xNot
*Pointer and prints the inverted input in binary form.  
*[Input]:Unsigned char _x in decimal form. 
*[return]: _xNot in Decimal form and printing _xNot in binary form.
*[Errors]:NO Errors
*******************************************************************************/
void InvertBits(unsigned char _x, unsigned char *_xNot);

/*******************************************************************************
*[Description]:RotateBits, Rotat unsigned char x _n times and return the answer 
*in _xRot Pointer and prints the Rotat input in binary form.  
*[Input]:Unsigned char _x in decimal form, _n rotations number and Pointer for
*saving answere.  
*[return]: _xRot in Decimal form and printing _xRot in binary form.
*[Errors]:NO Errors
*******************************************************************************/
void RotatetBits(unsigned char _x, size_t _n, unsigned char *_xRot);

/*******************************************************************************
*[Description]:function setbits(x,p,n,y) that returns x with the n bits that 
*begin at position p set to the rightmost n bits of an unsigned char variable y
*(leaving other bits unchanged).  
*[Input]:Unsigned char _x in decimal form, _n, _p and _y.  
*[return]: _x with set bits in _n,_p region.
*[Errors]:NO Errors.
*******************************************************************************/
int SetBits(unsigned char _x, size_t _p, size_t _n, unsigned char _y, unsigned char *_answere);

    /*******************************************************************************
*[Description]:function setbits(w,i,j,value) sets the bits from i to j (inclusive)
*to given value (0 or 1). 
*[Input]:Unsigned int _x in decimal form, _i, _j and value (0,1).  
*[return]: _x with set bits in _n,_p region.
*[Errors]:NO Errors.
*******************************************************************************/
int SetBitsByValue(unsigned int _w, size_t _i, size_t _j, size_t value, unsigned int *_answere);


void DisplayUCBits(unsigned char _input);
void DisplayUIBits(unsigned int _input);
#endif /*_BITWISEOP_H_*/
