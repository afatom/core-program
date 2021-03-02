#include <stdio.h>

void foo2(int _k);

typedef void (*funp)(int x);
typedef int (*funptr)(void);


funp ptr = foo2;

void foo1(int _i, int i1,int i2,int i3,int i4,int i5,int i6,int i7,int i8,int i9)
{
	int x;
	
	long j[10]={1,2,3,4,5,6,7,8,9};
	
	
	int * runhack=NULL;
	long* hack = NULL; /*<< my evil pointer*/
	
	
	
	
	
	printf("J[9]  %ld    &J[9] %p\n",j[9],&j[9]);
	hack = &j[9];
	runhack = &j[9];
	puts("stack image");
	
	for(x = 0; x < 10*sizeof(int); ++x)
	{
		printf("%p\t\t0x%x\n",runhack,*runhack);
		++runhack;	
	}
	
	hack+=4;
	*hack=foo2;
	/*
	rt = &j[9];
	rt = rt + 32/sizeof(int);
 	printf("rt pointer %p\n",*rt);
 	rt=ptr;*/
	/*
	hack = 0x40000c2;
	*hack = ;*/
return;
}


void foo2(int _k)
{
	int arr[10]= {10,11,12,13,14,15,16,17,18,19};
	puts("Life is Cool. No More Main Again!");
	printf("%d %d\n",arr[0],_k);
	return;
	
}


int main (void)
{
	funptr x = main;
	printf(">>>>>>>> Main address = %p\n\n",(void*)x);
	printf(">>>>>>>> Foo1 address = %p\n",(void*)foo1);
	printf(">>>>>>>> Foo2 address = %p\n",(void*)foo2);
	
	int i=33;
	
	foo1(i,i+1,i+2,i+3,i+4,i+5,i+6,i+7,i+8,i+9);
	puts("********************************");
	printf("Main !!\n");
	puts("********************************");
	
	return 0;

}

