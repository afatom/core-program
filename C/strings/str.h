#ifndef _STR_H_
#define _STR_H_

/*Convert an integer to a string. The function Myitoa() converts the integer
* value from val into an ASCII.
*representation that will be stored under str. The caller is responsible for providing sufficient storage in str.
*If the buffer is too small, you risk a buffer overflow.
*Only If radix is 10 and val is negative, a minus sign will be prepended (in other cases Minus sign will skipped)
*The itoa() function returns the pointer passed as s.
*Conversion is done using the radix as base, which may be a number between 2 (binary conversion) and up to 10.
**************************************************************************************************************/
int Myitoa(int val, char *str, int base);

/*The  myatoi() function converts the initial portion of the string pointed
to by str to int. 
RETURN VALUE : The converted value
*/
//int Myatoi(const char *str);
int Myatoi (const char* str, int* result);

int GetBase(int Number, int Base);

int RevNum(int num);

void RevStr(char *str);
#endif /*"_STR_H_"*/