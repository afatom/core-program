#include "draw.h"
#include <stdio.h>

void triangleOneDrawing    (char charToPrint, int size)
{
  if (size <= 0)
  {
    printf("Unvalid Input !\n");
    return;
  }
  for (int i=0; i<size; ++i)
  {
    for (int j=0; j<i+1;++j)
    {
      printf("%c", charToPrint);
    }
    printf("\n");
  }
  return;
}
void triangleTwoDrawing    (char charToPrint, int size)
{
  if (size <= 0)
  {
    printf("Unvalid Input !\n");
    return;
  }
  for (int i=size; i>0; --i)
  {
    for (int j=0; j<i;++j)
    {
      printf("%c", charToPrint);
    }
    printf("\n");
  }
  return;
}
void triangleThreeDrawing  (char charToPrint, int size)
{
  if (size <= 0)
  {
    printf("Unvalid Input !\n");
    return;
  }
  triangleOneDrawing    (charToPrint, size);
  triangleTwoDrawing    (charToPrint, size-1);
  return;
}
void triangleFourDrawing   (char charToPrint, int size)
{
  if (size <= 0)
  {
    printf("Unvalid Input !\n");
    return;
  }
  for (int i=size; i>0;--i)
  {
    for (int j=0; j<i;++j)
    {
      printf(" ");
    }
    for (int l=size; l>i;--l)
    {
    printf("%c", charToPrint);
    }
    printf("\n");
  }
  return;
}
void triangleFiveDrawing   (char charToPrint, int size);
void diamondDrawing        (char charToPrint, int size);
