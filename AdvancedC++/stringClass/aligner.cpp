
#include <iostream>

using namespace std;


typedef void(*fp)(void);



int main()
{
	aligner X;
	
	size_t m = sizeof(X) - sizeof(X.d);
	
	cout<<m<<endl;
	return 0;
}
