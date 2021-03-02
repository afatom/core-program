

#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;


void change(int* &ptr, int* dest)
{
	ptr = dest;
}



int main(void)
{
	int arr[10];
	int brr[5];
	
	cout<<"arr "<<arr<<endl;
	cout<<"brr "<<brr<<endl;
	int* aptr=arr;
	
	cout<<"Before "<<aptr<<endl;
	change(aptr,brr);
	cout<<"after "<<aptr<<endl;
	
	return 0;
}
