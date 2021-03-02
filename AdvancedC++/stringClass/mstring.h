#ifndef __STRING_H_
#define __STRING_H_


#include <iString.h>
#include <iostream>
#include <String.h>

class String : public IString{
	public:
	virtual ~String();
	String();
	String(char);
	String(const char*);
	String(const String&);
	String& operator = (const String&);
	String& operator = (const char*);
	
	//methods
	virtual inline size_t Length() const; 
	IString& Concat(const String&);
	virtual inline const char* C_Str() const;
	virtual IString& ToUpper();
	virtual IString& ToLower();
	virtual IString& Reverse();
	IString& operator += (const String&);
	virtual IString& operator += (const char*);
	virtual IString& operator += (char);
	virtual char& operator[] (size_t pos);
	virtual const char& operator[] (size_t pos) const {}	
	
		

	
	static void SetDefaultCapacity(size_t size);
	static size_t GetDefaultCapacity();
	

	private:
	char* m_buffer;
	size_t m_currentFreeCapacity;
	size_t m_currentCapacity;
	static size_t m_defCapacity;
	size_t Align(size_t);

	};


	inline size_t String::Length() const 
	{
		return strlen(this->m_buffer);
	}

	inline const char* String::C_Str() const
	{
		return this->m_buffer;
	}

	//Global Functions
	std::ostream& operator << (std::ostream& os, const IString& str);
	std::istream& operator >> (std::istream& is, IString& str);
	String operator+ (const String& lhs, const String& rhs);
	String operator+ (const String& lhs, const char*   rhs);
	String operator+ (const char*   lhs, const String& rhs);	
	String operator+ (const String& lhs, char          rhs);
	String operator+ (char          lhs, const String& rhs);
	String operator< (const String& lhs, const String& rhs);
	String operator== (const String& lhs, const String& rhs);
	String operator!= (const String& lhs, const String& rhs);




#endif //__STRING_H_
