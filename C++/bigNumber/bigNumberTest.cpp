#include <BigNumber.h>
#include <string>
#include <iostream>
#include <BigFloat.h>

using namespace std;


int main (int argc, char* argv[])
{
	
	/*
	BigNumber_t num1(argv[1]);
	BigNumber_t num2(argv[2]);
	
	
	BigNumber_t x(num1);
	
	
	BigNumber_t num3;
	num3 = num1 - num2;
	//num3 = num1 - num2;
	
	
	cout<<num3<<endl;
	
	*/
	/*
	BigNumber_t num33("562");
	BigNumber_t num44("1");
	BigNumber_t res;
	res = num44 - num33;
	cout<<res<<endl;
	*/
	
	
	BigFloat_t x1(argv[1]);
	BigFloat_t x2(argv[2]);
	BigFloat_t x3; 
	x3 = x1+x2;
	
	cout<<"Addition Result: "<<x3<<endl;
	cout<<"Substraction Result: "<<x1-x2<<endl;
	
	return 0;
}
