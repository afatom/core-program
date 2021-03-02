#include <stdio.h>
#include <stdlib.h>

typedef struct per {

	char a;
	int c;
	char x;

}per;

typedef struct per2 {

	char a;
	long c;
	char x;

}per2;

int main ()
{
	per p;
	per2 l;
	printf("Sizeof int is : %lu\n", sizeof(int));
	printf("Sizeof long is : %lu\n", sizeof(long));
	printf("Sizeof str is : %lu\n", sizeof(p));
	printf("Sizeof per2 is : %lu\n", sizeof(l));
	
	
return 0;
}
