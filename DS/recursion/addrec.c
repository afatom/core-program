#include <stdio.h>

void swap (char* one, char* sec)
{
	char temp = *sec;
	*sec = *one;
	*one = temp;
}

char ReverseCharArr(char* _str, char* helpChar)
{
	char temp;
	if (*_str=='\0')
	{
		return *(_str-1);
	}
	swap(*str, );
	*helpChar = *_str;
	printf("%c",*(_str));
	return (ReverseCharArr(++_str,helpChar));
}


int main ()
{
char str[4]="ABC";
char help;
ReverseCharArr(str, &help);
return 0;
}
