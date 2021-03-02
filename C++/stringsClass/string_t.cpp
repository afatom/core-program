#include "string_t.h"
#include <iostream>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <ctype.h>
#include <ios> 
#include <istream> 
#include <ostream>
#include <iomanip>      // std::setw

using namespace std;

bool string_t::caseSens = true; //work as before. default work
size_t string_t::capacity = 16;



size_t string_t::AlignToWordSize(size_t _size)
{
	size_t shift = 0;
	if(!_size)
	{
		return 2;
	}
	
	while(_size > 0)
	{
		++shift;
		_size = _size >> 1;
	}
	
	return (1 << shift);
}




string_t::string_t()
{
	buf = new char[capacity];
	buf[0]='\0';
	length = capacity; //object will born with default capacity
} 




void string_t::SetCapacity(size_t _capacity)
{
	capacity = AlignToWordSize(_capacity);
	return;
}

size_t string_t::GetCapacity(void)const
{
	return capacity;
}


string_t::~string_t()
{
	delete[] buf;
	buf = NULL; //for double free isuues
}

string_t::string_t(const char* _str)		//CTOR from "const char*"
{
	if(!_str)
	{
		buf = new char[capacity];
		buf[0]='\0';
		length = capacity;
		return;
	}
	
	if(strlen(_str) >= capacity)
	{
		size_t alignSize = AlignToWordSize(strlen(_str) + capacity);
		buf = new char[alignSize];
		length = alignSize;  //change length of this Obj only!
		strcpy(buf,_str);
		return;
	}
	size_t alignSize = AlignToWordSize(strlen(_str) + capacity);  
	buf = new char[alignSize];
	length = alignSize;
	strcpy(buf,_str);
	return;
}

string_t string_t::operator()(size_t start, size_t length)
{
	string_t newString;
	size_t len = StrLength();
	if(start > len)
	{
		return newString;
	}
	else if(start < len && length <= len)
	{
		strncat( newString.buf, &buf[start], length);
	}
	else {
		strncat( newString.buf, &buf[start], len);
	}
	
	return newString;
}



int string_t::GetFirstOccur(const char _ch)const
{
	char *ptrf=0;
	const char *ptri=buf;
	size_t size = StrLength(); 
	if(_ch == '\0')
	{
		return (int)size;
	}
	
	ptrf = strchr(buf, _ch);
	if(!ptrf)
	{
		return -1;
	}
	
	return (int)(ptrf - ptri);
}

int string_t::GetLastOccur(const char _ch)const
{
	char *ptrf=0;
	const char *ptri=buf;
	size_t size = StrLength(); 
	if(_ch == '\0')
	{
		return (int)size;
	}
	
	ptrf = strrchr(buf, _ch);
	if(!ptrf)
	{
		return -1;
	}
	return (int)(ptrf - ptri);
}



string_t& string_t::operator=(const string_t& _str) 
{
	char* newBuffer;
	
	if(this == &_str)
	{
		return *this;
	}
	
	if(strlen(_str.buf) < length)
	{
		strcpy(buf,_str.buf);
		return *this;
	}
	size_t alignSize = AlignToWordSize(strlen(_str.buf) + capacity); 
	newBuffer = new char[alignSize];
	length = alignSize;
	delete[] buf;
	buf = newBuffer;
	strcpy(buf,_str.buf);
	return *this;
}






string_t::string_t(const string_t& _str) 	//copy CTOR//he is constructor. again we need to allocate buf
{
	char* newBuffer;
	buf = new char[capacity];
	buf[0]='\0';
	length = capacity;
	
	if(strlen(_str.buf) < length )
	{
		strcpy(buf ,_str.buf);
		return;
	}
	size_t alignSize =AlignToWordSize(strlen(_str.buf) + capacity);
	newBuffer = new char[alignSize];
	length = alignSize;
	delete[] buf;
	buf = newBuffer;
	strcpy(buf,_str.buf);
	return;
}

/*


size_t string_t::StrLength()const
{
	return strlen(this->buf);
}
* 
* */

/*
const char* string_t::GetStr()const
{
	return buf;
}
*/
void string_t::SetStr(const char* _set)
{
	size_t inputLength =0;
	
	if(!_set)
	{
		return;
	}
	
	inputLength = strlen(_set);
	
	if(inputLength < length)
	{
		strcpy(buf,_set);
		return;
	}
	
	delete[] buf;
	size_t alignSize =AlignToWordSize(inputLength + capacity);
	buf = new char[alignSize];
	strcpy(buf,_set);
	return;
}

//int strcasecmp(const char *s1, const char *s2);


bool string_t::GetCaseSensFlag()const //true=on
{
	return caseSens;
}

void string_t::SetCaseSens(bool state) //true=on false=off
{
	caseSens = state;
	return;
}


int string_t::String_tCompare(const string_t& _str)const
{
	
	int cmp =0;
	if(caseSens == true)
	{
			
		cmp=strcmp(buf,_str.buf);
		if(cmp==0)
		{
			return 0;
		}
		else if(cmp < 0)
		{
			return 1;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		cmp=strcasecmp(buf,_str.buf);
		if(cmp==0)
		{
			return 0;
		}
		else if(cmp < 0)
		{
			return 1;
		}
		else
		{
			return 2;
		}
		
	}
}


void string_t::Print()const
{
	puts(this->buf);
}

void string_t::ConvStrToUpperCase()
{
	
	int i = 0;
	while( buf[i] ) 
	{
		buf[i] = (char)(toupper(buf[i]));
		++i;
	}	
}


void string_t::ConvStrToLowerCase()
{
	
	int i = 0;
	while( buf[i] ) 
	{
		buf[i] = (char)(tolower(buf[i]));
		++i;
	}	
}

void string_t::StrConcat(const char* _str)
{
	size_t len;
	char* concatString;
	
	len =strlen(_str);
	if(len + StrLength() < length)
	{
		strcat(buf,_str);
		return;
	}
	size_t align = AlignToWordSize(length + len);
	concatString = new char[align];
	strcat(concatString,buf);
	strcat(concatString,_str);
	SetStr(concatString);
	delete[]concatString;
	return;
	
}






void string_t::StrConcat(const string_t& _str)
{
	this->StrConcat(_str.buf);
	return;
}


string_t& string_t::operator+=(const char* _str) 
{
	size_t len;
	char* concatString;
	
	if(!_str)
	{
		return *this;
	}

	len =strlen(_str);
	if(len + StrLength() < length)
	{
		strcat(buf,_str);
		return *this;
	}
	size_t align = AlignToWordSize(length + len);
	concatString = new char[align];
	strcat(concatString,buf);
	strcat(concatString,_str);
	SetStr(concatString);
	delete[]concatString;
	return *this;
}


string_t& string_t::operator+=(const string_t& _str) 
{
	size_t len;
	char* concatString;

	len = _str.StrLength();
	if(len + StrLength() < length)
	{
		strcat(buf,_str.buf);
		return *this;
	}
	size_t align = AlignToWordSize(length + len);
	concatString = new char[align];
	strcat(concatString,buf);
	strcat(concatString,_str.buf);
	SetStr(concatString);
	delete[]concatString;
	return *this;
}





void string_t::Prepend(const char* _str)
{
	size_t len=0;
	size_t objlen=0;
	
	char* concatString;
	
	char* temp = new char[strlen(buf)];
	strcpy(temp,buf);
	
	objlen = StrLength();
	len =strlen(_str);
	
	if(len + objlen < length)
	{
		strcpy(buf,_str);
		strcat(buf,temp);
		delete[]temp;
		return;
	}
	size_t align = AlignToWordSize(len + objlen);
	
	concatString = new char[align];
	strcpy(concatString,_str);
	strcat(concatString,temp);
	SetStr(concatString);
	delete[]temp;
	delete[]concatString;
	return;
	
}

void string_t::Prepend(const string_t& _str)
{
	this->Prepend(_str.buf);
	return;
}


bool string_t::IsEqual(const string_t& _str)const
{
	if(!caseSens)
	{
		if(!strcasecmp(buf,_str.GetStr()))
		{
			return true;
		}
		
		return false;
		
	}
	else
	{	
		if(!strcmp(buf,_str.GetStr()))
		{
			return true;
		}
		
		return false;
	}
	
}


bool string_t::Isdefferent(const string_t& _str)const
{
	if(!caseSens)
	{
		if(strcasecmp(buf,_str.GetStr()))
		{
			return true;
		}
		
		return false;
	}
	
	else
	{
		if(strcmp(buf,_str.GetStr()))
		{
			return true;
		}
		
		return false;
	}
}

bool string_t::IsBigger(const string_t& _str)const
{
	if(!caseSens)
	{
		if((strcasecmp(buf,_str.GetStr())) > 0)
		{
			return true;
		}
		
		return false;
	}
	
	else
	{
		if((strcmp(buf,_str.GetStr())) > 0)
		{
			return true;
		}
		
		return false;
	}
}

bool string_t::IsSmaller(const string_t& _str)const
{
	if(!caseSens)
	{			
		if((strcasecmp(buf,_str.GetStr())) < 0)
		{
			return true;
		}
		
		return false;
	}
	else
	{
		if((strcmp(buf,_str.GetStr())) < 0)
		{
			return true;
		}
		
		return false;
	}
}

bool string_t::IsBiggerOrEqual(const string_t& _str)const
{
	if(!caseSens)
	{
			
		if((strcasecmp(buf,_str.GetStr())) >= 0)
		{
			return true;
		}
		
		return false;
	}
	else
	{
			
		if((strcmp(buf,_str.GetStr())) >= 0)
		{
			return true;
		}
		
		return false;
	}
	
}


bool string_t::IsSmallerOrEqual(const string_t& _str)const
{
	if(!caseSens)
	{
		if((strcasecmp(buf,_str.GetStr())) <= 0)
		{
			return true;
		}
		
		return false;
	}
	
	else
	{
		if((strcmp(buf,_str.GetStr())) <= 0)
		{
			return true;
		}
		
		return false;
	}

}

bool string_t::IsContains(const string_t& _str)const //ist calling obj contains str 
{
	char* retval = 0;
	if(!caseSens)
	{
		
		if((retval = strcasestr(buf, _str.GetStr())))
		{
			return true;
		}
		return false;
		}
	else
	{
	
		if((retval = strstr(buf, _str.GetStr())))
		{
			return true;
		}
		return false;	
	}
}





ostream& operator<<(ostream& os, const string_t& str)
{
	os<<str.GetStr();

	return os;
}

#define CIN_CAPACITY 16

istream& operator>>(istream& is, string_t& str)
{
	char isbuffer[CIN_CAPACITY];
	cin >> setw(CIN_CAPACITY) >> isbuffer;
	str.SetStr(isbuffer);
	return is;
	
}


//char& string_t::operator[](size_t i);
/*
char string_t::operator[](int i)const
{
	
	if(i > StrLength() || i < 0 )
	{
		return '\0';
	}
	
	return buf[i]; 
}
	
*/

char string_t::operator[](int index)const
{
	if(index < 0 || index > (int)StrLength()-1)
	{
		return '\0';
	}
	
	return this->buf[index];
}

char& string_t::operator[](int index)
{
	if(index < 0 || index > (int)StrLength()-1)
	{
		return this->buf[index+1];//i dont understand why index+1
	}
	return this->buf[index];
}

	

