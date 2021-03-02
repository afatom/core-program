#ifndef __BITS_H_
#define __BITS_H_
#include <stddef.h>

/** 
 *  @file Bits.h
 *  @brief basic ops on bits
 * 
 *  @author adham  faresadham@gmail.com
 * 
 *  @bug No known bugs.
 */

/** 
 * @brief Convert binary in stream to Hex form.
 * 
 * @param _less: binary in stream and bufferout for return value.
 * @return converted to hex stream (bufferout) and pointer to buffer out.
 * @retval 
 * @warning: capcity of bufferout must be at least length binaryin devided by 4 
 * plus one for terminating string.
 */
char* BinaryToHex(unsigned int binaryin, char* bufferout);
/** 
 * @brief Convert input number to its ABS value.
 * 
 * @param _less: input number (as achar).
 * @return ABS(num).
 * @retval 
 * @warning: 
 */
char AbsCalculator(char _num);
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

#endif /*<< __BITS_H_*/