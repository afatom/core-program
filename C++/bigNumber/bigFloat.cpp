#include <string>
#include <BigFloat.h>
#include <BigNumber.h>
#include <iostream>
using namespace std;



BigFloat_t::BigFloat_t():BigNumber_t()
{ }


BigFloat_t::BigFloat_t(const char* _number):BigNumber_t(_number)
{ }


BigFloat_t::BigFloat_t(BigFloat_t& _bigNumber):BigNumber_t(_bigNumber)
{ }


BigFloat_t::BigFloat_t(const string _number):BigNumber_t(_number)
{ }

BigFloat_t& BigFloat_t::operator = (const BigFloat_t& _bigNumber)
{
	this->SetNumber(_bigNumber.GetNumber());
	return *this;
}





BigFloat_t BigFloat_t::operator + (BigFloat_t& _bigNumber)
{
	
	string str1 = this->GetNumber();
	string str2 = _bigNumber.GetNumber();
	
	size_t len1=0,len2=0, finalPointPos=0, delta=0;
	
	len1 = str1.length();//this
	len2 = str2.length();
	size_t posOfPointInStr1 = str1.find_first_of(".");
	size_t posOfPointInStr2 = str2.find_first_of(".");
	
	
	if(len1 -1 - posOfPointInStr1 >= len2 -1 - posOfPointInStr2)
	{
		finalPointPos = len1 -1 - posOfPointInStr1 ;
		//Add zeroz to str2 at the back
		delta = (len1 -1 - posOfPointInStr1)-(len2 -1 - posOfPointInStr2);
		for(size_t j =0; j<delta; ++j)
		{
			str2.push_back('0');
		}
	}
	else
	{
		finalPointPos = len2 -1 - posOfPointInStr2 ;
		delta = (len2 -1 - posOfPointInStr2)-(len1 -1 - posOfPointInStr1);
		for(size_t j =0; j<delta; ++j)
		{
			str1.push_back('0');
		}
	}
	
	str1.erase (posOfPointInStr1,1);
	str2.erase (posOfPointInStr2, 1);
	
	BigNumber_t x1(str1);
	BigNumber_t x2(str2);
	BigNumber_t res; 

	
	res = x1 + x2;

	string getter = res.GetNumber();


	getter.insert(finalPointPos , 1, '.');
	res.SetNumber(getter);
	//cout<<res<<endl;
	BigFloat_t result(res.GetNumber());
	return result;
}


BigFloat_t BigFloat_t::operator - (BigFloat_t& _bigNumber)
{


	string str1 = this->GetNumber();
	string str2 = _bigNumber.GetNumber();
	
	size_t len1=0,len2=0, finalPointPos=0, delta=0;
	
	len1 = str1.length();//this
	len2 = str2.length();
	size_t posOfPointInStr1 = str1.find_first_of(".");
	size_t posOfPointInStr2 = str2.find_first_of(".");
	
	if(len1 -1 - posOfPointInStr1 >= len2 -1 - posOfPointInStr2)
	{
		finalPointPos = len1 -1 - posOfPointInStr1 ;
		//Add zeroz to str2 at the back
		delta = (len1 -1 - posOfPointInStr1)-(len2 -1 - posOfPointInStr2);
		for(size_t j =0; j<delta; ++j)
		{
			str2.push_back('0');
		}
	}
	else
	{
		finalPointPos = len2 -1 - posOfPointInStr2 ;
		delta = (len2 -1 - posOfPointInStr2)-(len1 -1 - posOfPointInStr1);
		for(size_t j =0; j<delta; ++j)
		{
			str1.push_back('0');
		}
	}
	
	str1.erase (posOfPointInStr1,1);
	str2.erase (posOfPointInStr2, 1);
	
	BigNumber_t x1(str1);
	BigNumber_t x2(str2);
	BigNumber_t res; 
	
	res = x1 - x2;
	string getter = res.GetNumber();

	getter.insert(finalPointPos, 1, '.');
	res.SetNumber(getter);

	BigFloat_t result(res.GetNumber());
	return result;
}

