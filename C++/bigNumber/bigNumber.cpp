#include <BigNumber.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;




BigNumber_t::BigNumber_t(const char* _number)
{
	if(!_number)
	{
		m_num = '0';
		return;
	}
	
	m_num = _number; //String CTOR from char* and then asignment
}

BigNumber_t::BigNumber_t(int _number)
{
	char temp[16];
	//itoa ( _number, temp, 10 );
	sprintf(temp,"%d",_number);
	m_num = temp;
}


BigNumber_t::BigNumber_t(string _number)
{
	m_num = _number;
}
	



BigNumber_t::BigNumber_t(BigNumber_t& _bigNumber) //copy CTOR
{
	m_num = _bigNumber.m_num;
}


bool BigNumber_t::operator == (const BigNumber_t& _bigNumber)const
{
	return (this->m_num == _bigNumber.m_num) ? (true) : (false);	
}


bool BigNumber_t::operator < (const BigNumber_t& _bigNumber)const
{
	if(m_num.length() < _bigNumber.m_num.length())
	{
		return true;
	}
	
	if(m_num.length() > _bigNumber.m_num.length())
	{
		return false;
	}
	
	if(m_num.compare(_bigNumber.m_num) < 0)
	{
		return true;
	}
	return false;
}


bool BigNumber_t::operator > (const BigNumber_t& _bigNumber)const
{
	if(m_num.length() > _bigNumber.m_num.length())
	{
		return true;
	}
	
	if(m_num.length() < _bigNumber.m_num.length())
	{
		return false;
	}
	
	if(m_num.compare(_bigNumber.m_num) > 0)
	{
		return true;
	}
	return false;
}
	
BigNumber_t& BigNumber_t::operator = (const BigNumber_t& _bigNumber)
{
	this->m_num = _bigNumber.m_num;
	return *this;
}

BigNumber_t& BigNumber_t::operator = (int _number)
{
	BigNumber_t val(_number);
	this->m_num = val.m_num;
	return *this;
}


bool BigNumber_t::operator == (int _number)const
{
	BigNumber_t num(_number);
	return (this->m_num == num.m_num) ? (true) : (false);
}

int BigNumber_t::GetMin(size_t _first, size_t _sec)
{
	if(_first < _sec)
	{
		return _first;
	}
	
	return _sec;
}
	
int BigNumber_t::GetMax(size_t _first, size_t _sec)
{
	if(_first < _sec)
	{
		return _sec;
	}
	
	return _first;
}

BigNumber_t BigNumber_t::operator + (BigNumber_t& _bigNumber)
{
	BigNumber_t result;
	if(m_num[0]=='-' || _bigNumber.m_num[0]=='-')
	{
		return result;
	}
	
	int len1 = 0, len2 =0, val1 =0, val2=0, sum=0, carry =0, max = 0, min =0;
	
	// Take an empty string for storing result
    string additionResult = " ";
   
    if (m_num.length() > _bigNumber.m_num.length())
	{
        m_num.swap(_bigNumber.m_num);	
	}
	
	len1 = m_num.length(); //bigger num
	len2 = _bigNumber.m_num.length();
	
	int i = 0;
	int delta = len2-len1;
	for(i = len1-1; i >= 0; --i)
	{
		sum = ((m_num[i]-'0') + (_bigNumber.m_num[i+delta]-'0') + carry);
	   //additionResult[i] = (char)(sum%10 + '0');
	   additionResult.push_back(sum%10 + '0');
	   carry=sum/10;
	}
		
	
	for(int j = len2-len1-1; j >=0; --j)
	{
		sum = (_bigNumber.m_num[j]-'0') + carry;
		//additionResult[i] = (char)(sum%10 + '0');
		additionResult.push_back(sum%10 + '0');
		carry=sum/10;
	}	
	
	if(carry)
	{
		//additionResult[i] = carry + '0';
		additionResult.push_back(carry + '0');
	}
	
    reverse(additionResult.begin(), additionResult.end());
    
    result.m_num = additionResult;
	return result;
}

ostream& operator<<(ostream& os, const BigNumber_t& _number)
{
	os << "Number: "<<_number.GetNumber();
	return os;
}
	
#define CIN_CAPACITY 64

istream& operator>>(istream& is, BigNumber_t& _number)
{
	char isbuffer[CIN_CAPACITY];
	cin >> setw(CIN_CAPACITY) >> isbuffer;
	_number.SetNumber(isbuffer);
	return is;
}


void BigNumber_t::SetNumber(const char* _num)
{
	if (!_num)
	{
		return;
	}
		 
	this->m_num = _num;
}


void BigNumber_t::SetNumber(const string& _num)
{
	m_num = _num;
}

int BigNumber_t::BorrowFunction(string& _number, int _index)
{
	for(int j = _index-1; j >= 0; --j)
	{
		if(_number[j]-'0' > 0) //can u borrow me?
		{
			int temp = _number[j]-'0' -1;
			_number[j] = temp + '0';
			if(_number[j+1] == '0')
			{
				_number[j+1] = '1';
				return 0; //call borrow function again
			}
			else
			{
				return (10 + _number[j+1] - '0');
			} 
		}
	}
	
	//if we reach this point. there is no number to borrow from.  
	//dont call again
	return -1;
}

/*
BigNumber_t BigNumber_t::operator - (BigNumber_t& _bigNumber)
{
	BigNumber_t result;
	char sign = '+';
	int len1 = 0, len2 =0, val1 =0, val2=0, sum=0, carry =0, max = 0, min =0;
	
	if(m_num[0]=='-' || _bigNumber.m_num[0]=='-')
	{
		return result;
	}
	
	// Take an empty string for storing result
    string substractionResult = " ";
    
   	len1 = m_num.length(); 
	len2 = _bigNumber.m_num.length();
	
	if(len1 < len2)
	{
		//add leading zeroz on m_num
		reverse(m_num.begin(), m_num.end());
		for(int i = len2-len1 ;i>0 ;--i)
		{
			m_num.push_back('0');
		}
		reverse(m_num.begin(), m_num.end());
	}
	else if(len2 < len1)
	{
		//add leading zeroz on _bigNumber.m_num
		reverse(_bigNumber.m_num.begin(), _bigNumber.m_num.end());
		for(int i = len1-len2 ;i>0 ;--i)
		{
			_bigNumber.m_num.push_back('0');
		}
		reverse(_bigNumber.m_num.begin(), _bigNumber.m_num.end());
	}
	
	cout<<m_num<<endl;
	cout<<_bigNumber.m_num<<endl;
	
	
	
	
	return result;
	
	
}
*/





BigNumber_t BigNumber_t::operator - (BigNumber_t& _bigNumber)
{
	BigNumber_t result;
	char sign = '+';
	int len1 = 0, len2 =0, sub=0, carry =0;
	
	if(m_num[0]=='-' || _bigNumber.m_num[0]=='-')
	{
		return result;
	}
	
	// Take an empty string for storing result
    string substractionResult = " ";
    
   	len1 = m_num.length(); 
	len2 = _bigNumber.m_num.length();
	
	if(len1 < len2)
	{
		//add leading zeroz on m_num
		sign = '-';
		m_num.swap(_bigNumber.m_num);
		len1 = m_num.length(); 
		len2 = _bigNumber.m_num.length();
		//add leading zeroz on _bigNumber.m_num
		reverse(_bigNumber.m_num.begin(), _bigNumber.m_num.end());
		for(int i = len1-len2 ;i>0 ;--i)
		{
			_bigNumber.m_num.push_back('0');
		}
		reverse(_bigNumber.m_num.begin(), _bigNumber.m_num.end());
		
	}
	else if(len2 < len1)
	{
		//add leading zeroz on _bigNumber.m_num
		reverse(_bigNumber.m_num.begin(), _bigNumber.m_num.end());
		for(int i = len1-len2 ;i>0 ;--i)
		{
			 _bigNumber.m_num.push_back('0');
		}
		reverse(_bigNumber.m_num.begin(), _bigNumber.m_num.end());
	}
	

	//cout<<m_num<<endl;
	//cout<<_bigNumber.m_num<<endl;
	
	for(int j= m_num.length()-1; j>=0;--j )
	{
		sub = ((m_num[j]-'0') - (_bigNumber.m_num[j]-'0') - carry);
        if (sub < 0 && m_num.length()>1)
        {
            sub += 10;
            carry = 1;
        }
        else if(sub < 0 && m_num.length()==1)
        {
			sub *= -1;
			sign = '-';
		}
        else
        {
			carry = 0;
		}
         
        substractionResult.push_back(sub + '0');
	}
	
	if(sign == '-')
	{
		substractionResult.push_back('-');
	}
	
	reverse(substractionResult.begin(), substractionResult.end());
    result.m_num = substractionResult;
	return result;	
}
