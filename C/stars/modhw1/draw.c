#include "draw.h"
#include <stdio.h>

#define MAX_SIZE 40
#define MAX_CHAR '~'
#define MIN_CHAR '!'

int CheckParams  (char charToPrint, int size)
{
  if (size<1 || size>MAX_SIZE)
  {
    return SIZE_NOT_VALID;
  }
  if (charToPrint<MIN_CHAR || charToPrint>MAX_CHAR)
  {
    return CHAR_TO_PRINT_NOT_VALID;
  }
  return OK;
}
void PrintChar (char charToPrint, int size)
{
  for (int j=0; j<size;++j)
  {
    printf("%c", charToPrint);
  }
  return;
}
void PrintBlank (int size)
{
  for (int j=0; j<size;++j)
  {
    printf(" ");
  }
  return;
}
void PrintCharBlank (char charToPrint, int size)
{
  for (int j=0; j<size;++j)
  {
    printf("%c ", charToPrint);
  }
  return;
}

void PrintBlankChar (char charToPrint, int size)
{
  for (int j=0; j<size;++j)
  {
    printf(" %c", charToPrint);
  }
  return;
}


int triangleOneDrawing    (char charToPrint, int size)
{
  int result;
  /*check params*/
  if ((result=CheckParams(charToPrint,size)) != OK)
  {
    return result;
  }
  for (int i=0; i<size; ++i)
  {
    PrintChar (charToPrint,i+1);
    printf("\n");
  }
  return OK;
}

int triangleTwoDrawing    (char charToPrint, int size)
{
  int result;
  /*check params*/
  if ((result=CheckParams(charToPrint,size)) != OK)
  {
    return result;
  }
  for (int i=size; i>0; --i)
  {
    PrintChar (charToPrint,i);
    printf("\n");
  }
  return OK;
}
int triangleThreeDrawing  (char charToPrint, int size)
{
  int result;
  /*check params*/
  if ((result=CheckParams(charToPrint,size)) != OK)
  {
    return result;
  }
  triangleOneDrawing    (charToPrint, size);
  triangleTwoDrawing    (charToPrint, size-1);
  return OK;
}
int triangleFourDrawing   (char charToPrint, int size)
{
  int result;
  /*check params*/
  if ((result=CheckParams(charToPrint,size)) != OK)
  {
    return result;
  }
  for (int i=size; i>=0;--i)
  {
    PrintBlank (i);
    PrintCharBlank (charToPrint, size-i);
    printf("\n");
  }
  return OK;
}
int triangleFiveDrawing   (char charToPrint, int size)
{
  int result;
  /*check params*/
  if ((result=CheckParams(charToPrint,size)) != OK)
  {
    return result;
  }
  for (int i=size; i>0;--i)
  {
    PrintCharBlank (charToPrint, i);
    printf("\n");
    PrintBlank (size+1-i);
  }
  return OK;
}
int diamondDrawing        (char charToPrint, int size)
{
  int result;
  /*check params*/
  if ((result=CheckParams(charToPrint,size)) != OK)
  {
    return result;
  }
  triangleFourDrawing (charToPrint, size);
  for (int i=size-1; i>=0;--i)
  {
    PrintBlankChar (charToPrint, i);
    printf("\n");
    PrintBlank(size-i);
  }
  return OK;
}
