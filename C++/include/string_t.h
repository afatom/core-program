#ifndef __STRING_T_H_
#define __STRING_T_H_

#include <stddef.h>
#include <ios> 
#include <istream> 
#include <ostream>
#include <iostream>
#include <string.h>

using namespace std;


class string_t {
public:				 				//Member functions
	
	string_t(); 					//default constructor - CTOR
	string_t(const char* _str);		//CTOR from "const char*"
	string_t(const string_t& str); 	//copy CTOR
	~string_t();					//destructor - DTOR
	string_t& operator=(const string_t& _str); //assignment operator
	string_t& operator+=(const char* _str);  //concat operator
	string_t& operator+=(const string_t& _str);  //concat operator
	string_t operator()(size_t start, size_t length);
	//char& operator[](size_t i);
	//char operator[](int i)const;
	void Print()const;
	inline size_t StrLength()const;
	const char* GetStr()const{return buf;}
	void SetStr(const char* _set);
	int String_tCompare(const string_t& _str);
	void ConvStrToUpperCase();
	void ConvStrToLowerCase();
	void Prepend(const char* _str);
	void Prepend(const string_t& _str);
	void StrConcat(const char* _str);
	void StrConcat(const string_t& _str);
	bool IsEqual(const string_t& _str); 		// ==
	bool Isdefferent(const string_t& _str);		// !=
	bool IsBigger(const string_t& _str);
	bool IsSmaller(const string_t& _str);
	bool IsBiggerOrEqual(const string_t& _str);
	bool IsSmallerOrEqual(const string_t& _str);
	bool IsContains(const string_t& _str); //ist calling obj contains str 
	static bool GetCaseSensFlag(); //true=on
	static void SetCaseSens(bool state); //true=on false=off
	static void SetCapacity(size_t _capacity);
	static size_t GetCapacity(void);
	int GetFirstOccur(const char _ch)const;
	int GetLastOccur(const char _ch)const;


	private:	//data Member
	char* buf;
	size_t length;
	static bool caseSens;
	static size_t capacity; //align to memory words
	static size_t AlignToWordSize(size_t _size); //align to 2^x
	};
	ostream& operator<<(ostream& os, const string_t& str);
	istream& operator>>(istream& is, string_t& str);
	
	inline size_t string_t::StrLength()const
	{
		return strlen(this->buf);
	}
	
	

#endif //__STRING_T_H_
