
//#include <mstring.h>"mstring.h"
#include <mstring.h>
#include <exception>
#include <cstring>
#include <iostream>

//using std::cout;
//using std::cin;


size_t String_t::m_defCapacity = 16;

typedef union 
{
	char v1;
	int v2;
	double v3;
	float v4;
	void* v5;
	void(*fp)(void);
	size_t v7;
	long v8;
	short v9;
}types;

typedef struct{
	char m1;
	types m2;
}aligner;




size_t String_t::Align(size_t _size)
{
	aligner X;
	size_t alignFactor = sizeof(X) - sizeof(X.m2);
	if(_size < alignFactor)
		return alignFactor;
		
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


String_t::~String_t()
{
	delete [] m_buffer;
}



String_t::String_t()
{

	m_buffer = new char[m_defCapacity];
	m_buffer[0]='\0';
	m_currentCapacity = m_currentFreeCapacity = m_defCapacity;
}


String_t::String_t(const char* _str)
{
	if(!_str)
	{
		m_buffer = new char[m_defCapacity];
		m_buffer[0]='\0';
		m_currentCapacity = m_currentFreeCapacity = m_defCapacity;
	}
	
	else if(strlen(_str) >= m_defCapacity)
	{
		size_t alignSize = Align(strlen(_str));
		m_buffer = new char[alignSize];
		strcpy(m_buffer,_str);
		m_currentFreeCapacity = alignSize - strlen(_str);
		m_currentCapacity = alignSize;
	}

	else
	{ 
		m_buffer = new char[m_defCapacity];
		strcpy(m_buffer,_str);
		m_currentFreeCapacity = m_defCapacity - strlen(_str);
		m_currentCapacity = m_defCapacity;
	}
}


String_t::String_t(const String_t& _str)
{
	if(_str.Length() > m_defCapacity)
	{
		size_t alignSize = Align(_str.Length());
		m_buffer = new char[alignSize];
		strcpy(m_buffer, _str.m_buffer);
		m_currentFreeCapacity = alignSize - _str.Length();
		m_currentCapacity = alignSize;
	}

	else
	{ 
		m_buffer = new char[m_defCapacity];
		strcpy(m_buffer, _str.m_buffer);
		m_currentFreeCapacity = m_defCapacity - _str.Length();
		m_currentCapacity = m_defCapacity;
	}
}



String_t& String_t::operator = (const String_t& str)
{
	if(&str == this)
	{
		return *this;
	}
	

	if(str.Length() <= m_currentCapacity)
	{
		strcpy(this->m_buffer, str.m_buffer);
		m_currentFreeCapacity = m_currentCapacity - str.Length();
		return *this;
	}

	size_t alignSize = Align(str.Length()); 
	char* newBuffer = new char[alignSize];
	delete [] m_buffer;
	m_buffer = newBuffer;
	strcpy(m_buffer, str.m_buffer);
	m_currentCapacity = alignSize;
	m_currentFreeCapacity = m_currentCapacity - str.Length();
	return *this;
}



IString_t& String_t::ToUpper()
{
	int i = 0;
	while( this->m_buffer[i]) 
	{
		this->m_buffer[i] = (char)(toupper(m_buffer[i]));
		++i;
	}
	return *this;	
}


IString_t& String_t::ToLower()
{
	int i = 0;
	while( m_buffer[i] ) 
	{
		this->m_buffer[i] = (char)(tolower(m_buffer[i]));
		++i;
	}
	return *this;	
}

IString_t& String_t::Reverse()
{
	char* leftStart = m_buffer;
	char* rightEnd = m_buffer -1 + strlen(m_buffer);
	while(leftStart < rightEnd)
	{
		char temp = *leftStart;
		*leftStart = *rightEnd;
		*rightEnd = temp;
		++leftStart;
		--rightEnd;
	}
	return *this;	 
}


IString_t& String_t::Concat(const String_t& str)
{
	size_t length = str.Length();
	if(m_currentFreeCapacity > length)
	{
		strncat(m_buffer, str.m_buffer, length);
	}

	else{
		size_t size = Align(length + m_currentCapacity);
		m_currentCapacity = size;
		char* ptr = m_buffer;
		char* newBuffer = new char[size];
		strcpy(newBuffer,m_buffer);
		delete [] ptr;
		m_buffer = newBuffer;
		strncat(m_buffer, str.m_buffer, length);
		m_currentFreeCapacity = m_currentCapacity - strlen(m_buffer);
	}

	return *this;

}


IString_t& String_t::operator += (const String_t& str)
{
	this->Concat(str);
	return *this;
}

IString_t& String_t::operator += (const char* str)
{
	String_t temp(str);
	this->Concat(temp);
	return *this;
}


String_t::String_t(char c)
{
	m_buffer = new char[m_defCapacity];
	m_buffer[0] = c;
	m_buffer[1] = '\0';
	m_currentCapacity = m_currentFreeCapacity = m_defCapacity - 1;
}


IString_t& String_t::operator += (char c)
{
	String_t temp(c);
	this->Concat(temp);
	return *this;
}

void String_t::SetDefaultCapacity(size_t size)
{

	String_t::m_defCapacity = size;
}

size_t String_t::GetDefaultCapacity()
{
	return String_t::m_defCapacity;
}


String_t operator+ (const string& lhs, const string& rhs)
{
	String_t temp; 
}


/*
String_t operator+ (const string& lhs, const char*   rhs);
String_t operator+ (const char*   lhs, const string& rhs);	

String_t operator+ (const string& lhs, char          rhs);
String_t operator+ (char          lhs, const string& rhs);*/