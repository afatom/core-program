#ifndef __STRING_H_
#define __STRING_H_

#include "buffer.h"

namespace advcpp {

template<typename T>
class String{
public:
	String(const char* str = "");
	
	String& ToUpper();
	String& ToLower();
	String& Reverse();
	char& operator[](size_t);
	const char& operator[](size_t) const;
	
	String& operator+= (String const& other);

private:
	size_t m_count;
	Buffer<T> m_buffer;
}; // class String


String operator+ (const String& lhs, const String& rhs)
{
	String temp();
	temp += lhs;
	temp += rhs;
	return temp;
}





template<typename T>
String<T>::String(const char* str)	
: m_count(strlen(str) + 1)
, m_buffer(m_count)
{
	std::copy(str, str + m_count, m_buffer.begin());
}

template<typename T>
String<T>::String& ToUpper()
{
	std::transform(m_buffer.begin(), m_buffer.begin() + m_count, m_buffer.begin(), std::toupper);
	return *this;
}

template<typename T>
String<T>::String& ToLower()
{
	std::transform(m_buffer.begin(), m_buffer.begin() + m_count, m_buffer.begin(), std::tolower);
	return *this;
}




template<typename T>
char& String<T>::operator[] (size_t index)
{
	return *(m_buffer.begin() + index);
}

template<typename T>
const char&String<T>::operator[] (size_t) const
{
	return *(m_buffer.begin() + index);
}

template<typename T>
String& String<T>::operator+= (String const& other)
{
	size_t tc = other.m_count + m_count - 1;
	if(m_buffer.capacity() < tc)
	{
		m_buffer.grow((tc * 3) / 2);
	}
	std::copy(other.begin(), other.end(), end()-1);
	return *this;
}

template<typename T>
String<T>::

template<typename T>
String<T>::

template<typename T>
String<T>::

template<typename T>
String<T>::



} // namespase advcpp

#endif /* __STRING_H_ */


   

   


























