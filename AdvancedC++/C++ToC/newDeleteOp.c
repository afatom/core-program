#include <stdlib.h>




size_t MyAllignement(void)
{
	union unit{
		char c1;
		int c2;
		double c3;
		float c4;
		
		
		};
	struct {
		char c;
		
}

typedef struct Rectangle{
	int data;
	}Rectangle ;


typedef struct header{
	size_t noe;
	}header;

void* MyNewRectangleArray(size_t noe)
{
	header head;
	head.noe = noe;
	Rectangle* arr = (Rectangle*)malloc(sizeof(header) + sizeof(Rectangle)*noe);
	arr = arr + sizeof(header);
	for(size_t i =0; i < noe; ++i)
	{
		//call dflt ctor for each rectangle pointer 
	}
	
	return arr;
}



void Mydelete(Rectangle* arr)
{
	size_t *fptr =  (size_t*)arr;
	--fptr;
	size_t noe= *fptr;
	for(size_t j=0; j < noe; ++j)
	{
		//call default dtor for arr[j]
	}
	
	free(arr);
}

int main(void)
{
	
	void* ptr = MyNewRectangleArray(2);
	Mydelete(ptr);
	
	return 0;
}
