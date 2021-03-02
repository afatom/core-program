#ifndef _DRAW_H_
#define _DRAW_H_

/*Errors*/
#define OK 0
#define SIZE_NOT_VALID 2
#define CHAR_TO_PRINT_NOT_VALID 1

/*[def] = first triangle drawing function
*[Inputs] = size should not exceed 40. only '!' - '~' chars allowed.
*[output] = 0 means success 1 means invalid char input, 2 means invalid size*/
int triangleOneDrawing    (char charToPrint, int size);

/*[def] = second triangle drawing function
*[Inputs] = size should not exceed 40. only '!' - '~' chars allowed.
*[output] = 0 means success 1 means invalid char input, 2 means invalid size*/
int triangleTwoDrawing    (char charToPrint, int size);

/*[def] = Third triangle drawing function
*[Inputs] = size should not exceed 40. only '!' - '~' chars allowed.
*[output] = 0 means success 1 means invalid char input, 2 means invalid size*/
int triangleThreeDrawing  (char charToPrint, int size);

/*[def] = fourth triangle drawing function
*[Inputs] = size should not exceed 40. only '!' - '~' chars allowed.
*[output] = 0 means success 1 means invalid char input, 2 means invalid size*/
int triangleFourDrawing   (char charToPrint, int size);

/*[def] = fifth triangle drawing function
*[Inputs] = size should not exceed 40. only '!' - '~' chars allowed.
*[output] = 0 means success 1 means invalid char input, 2 means invalid size*/
int triangleFiveDrawing   (char charToPrint, int size);

/*[def] = diamond drawing function
*[Inputs] = size should not exceed 40. only '!' - '~' chars allowed.
*[output] = 0 means success 1 means invalid char input, 2 means invalid size*/
int diamondDrawing        (char charToPrint, int size);

/*Shapes Plots Examples Here*/
/************************************
first shape:
*
**
***
****

second shape:
****
***
**
*

third shape:
*
**
***
****
***
**
*

fourth shape:
   *
  * *
 * * *
* * * *

fifth shape:
* * * *
 * * *
  * *
   *

diamond shape:
   *
  * *
 * * *
* * * *
 * * *
  * *
   *
*************************************/



#endif /*_DRAW_H_*/
