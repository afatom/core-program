#include <iostream>
#include <ctime>

using namespace std;



void print(int* arr, int size)
{
	for(int i =0; i < size; ++i)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

int main (int argc, char* argv[])
{
	srand((unsigned int)time(0));
	
	//argc= num of array elements
	//argv the elements
	int* arr = new int[argc-2];
	for(int i = 1; i < argc-1; ++i)
	{
		arr[i-1] = atoi(argv[i]);
	}
	
	int size = argc - 2; 
	int high=0,low=0,mid=0,midval=0;
	
	high = size - 1; //max elem index
	mid = high/2;
	midval = arr[mid];
	
	int wanted = atoi(argv[argc - 1]);
	
	cout<<"Wanted: " <<wanted<<endl;
			
	if(arr[high] < wanted)
	{
		cout<<"Not exist"<<endl;
		return 0;
	}
	
	if(arr[low] > wanted)
	{
		cout<<"Not exist"<<endl;
		return 0;
	}
	
	
	
	while(high>=low)
	{
		if(arr[mid] == wanted)
		{
			cout<<"wnated index "<<mid<<endl;
			delete[](arr);
			return 0;
		}
		
		if(arr[mid] > wanted)
		{
			high = mid-1;
		}
		else
		{
			low = mid+1;
		}
		
		mid = low + (high-1/2);
	}
	
	//print(arr,argc-1);
	cout<<"Not exist"<<endl;
	delete[](arr);
	
	return 0;	
}
