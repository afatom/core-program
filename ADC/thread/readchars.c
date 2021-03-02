#include <stdio.h>
#include <string.h>


int ReadInput(void)
{
	char str[10];
	scanf("%s",str);
	
	printf("%s",str);
	return (int)strlen(str);
}


int main (int argc, char* argv[])
{
	int count=0;
	puts("Please enter string");
	count=ReadInput();
	printf("Printed %d chars\n",count);
return 0;
}
