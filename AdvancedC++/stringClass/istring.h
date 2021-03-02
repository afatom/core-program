#ifndef __ISTRING_H_
#define __ISTRING_H_

#include <cstddef>


class IString{
	public:
	virtual ~IString(){}
	//IString(){}
	
	//methods
	virtual inline size_t Length() const = 0;
	//virtual IString& Concat(const IString&) = 0;
	virtual inline const char* C_Str() const = 0;
	virtual IString& ToUpper() = 0;
	virtual IString& ToLower() = 0;
	virtual IString& Reverse() = 0;
	//virtual IString& operator += (const IString&) = 0;
	virtual IString& operator += (const char*) = 0;
	virtual IString& operator += (char) = 0;
	virtual char& operator[] (size_t pos) = 0;
	virtual const char& operator[] (size_t pos) const = 0;
	
	private:
	
	};



#endif //__ISTRING_H_

