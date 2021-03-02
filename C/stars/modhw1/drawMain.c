#include "draw.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
  char charToPrint = '$';
  int size = 5;
  int result;
  result = triangleOneDrawing    (charToPrint, size);
  printf("\n\n");
  result = triangleTwoDrawing    (charToPrint, size);
  printf("\n\n");
  result = triangleThreeDrawing  (charToPrint, size);

  printf("\n\n");
  result = triangleFourDrawing   (charToPrint, size);
  printf("\n\n");
  result = triangleFiveDrawing   (charToPrint, size);

  result = diamondDrawing        (charToPrint, size);

  return 0;
}
