#ifndef _LOTO_H_
#define _LOTO_H_
#include <stdlib.h>

/*******************************************************************************
*[Description]:Filling array with stars acording to giving num
*[Input]:pointer array . rows and col. and num to fill
*[output]:array with stars in the wright places (Void)
*[Errors]: NO ERRORS void return
********************************************************************************/
void ArrayFill(char *arr, size_t raw, size_t col, size_t num);

/*******************************************************************************
*[Description]:Printing array to stdout after filling OP
*[Input]:Char array with givin raw and col size
*[output]:Printing array to stdout
*[Errors]: NO ERRORS void return
********************************************************************************/
void printarr(char *arr, size_t raw, size_t col);

/*******************************************************************************
*[Description]:Printing array to file stream after filling OP
*[Input]:pointer array . rows and col. and file name to write to
*[output]:txt file. 0 = function success  1 = function fails
*[Errors]: NO ERRORS void return
********************************************************************************/
int printToFile(char *arr, size_t raw, size_t col,const char* filename);

/*******************************************************************************
*[Description]:random number genretator function
*[Input]:No input
*[output]:random number (sizet type)
*[Errors]: NO ERRORS
********************************************************************************/
size_t NumbersLottery();

#endif /*_LOTO_H_*/