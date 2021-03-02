#include "draw.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
  char charToPrint = '*';
  int size =5;
  triangleOneDrawing    (charToPrint, size);
  printf("\n\n");
  triangleTwoDrawing    (charToPrint, size);
  printf("\n\n");
  triangleThreeDrawing  (charToPrint, size);
  printf("\n\n");
  triangleFourDrawing   (charToPrint, size);
  return 0;
}
