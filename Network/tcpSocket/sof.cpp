#include <iostream>

using namespace std;


typedef union{
	int x;
	char c;
} var;


int main()
{
	int arr[2];
	//cout<<&arr[1] - &arr[0];
	
	var mvar;
	
	mvar.x=1;
	
	cout<<mvar.x<<endl;
	
	cout<<"..."<<mvar.c<<endl;
	
	return 0;
}
