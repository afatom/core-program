#include <memManager_t.h>
#include <memPage_t.h>
#include <iostream>
#include <assert.h>
#include <memPool_t.h>

using namespace std;

#define TEST_ARRAY_SIZE 24

void arrInit(int* arr, int size);
void PrintArray(int* arr, int size);

int main(void)
{
	//size_t nob =0;
	MemPool_t pool1;
	int x_1 = 10; 	
	int y =0;
	int arr[2]={0};
	
	
	pool1.Write(&x_1, sizeof(x_1));
	pool1.Read(&y, sizeof(x_1));
	x_1 = 999;
	pool1.Write(&x_1, sizeof(x_1));
	pool1.Read(&arr[0], sizeof(x_1));
	pool1.Read(&arr[1], sizeof(x_1));
	
	PrintArray(arr, 2);
	return 0;
}




void arrInit(int* arr, int size)
{
	for(int i=0; i< size; ++i)
	{
		arr[i] = i;
	}
}

void PrintArray(int* arr, int size)
{
	for(int i = 0; i < size; ++i)
	{
		cout<<"arr["<<i<<"] = "  <<arr[i]<<endl;
	}
}	




