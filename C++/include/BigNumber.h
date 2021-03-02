#ifndef __BigNumber_H_
#define __BigNumber_H_

#include <string>
using namespace std;

class BigNumber_t{
	public:
	virtual ~BigNumber_t(){}
	BigNumber_t(){	m_num = '0';}
	BigNumber_t(const char* _number);
	BigNumber_t(string _number);
	
	BigNumber_t(int _number);
	BigNumber_t(BigNumber_t& _bigNumber); //copy CTOR
	
	BigNumber_t& operator = (const BigNumber_t& _bigNumber);
	BigNumber_t& operator = (int _number);
	
	virtual bool operator == (const BigNumber_t& _bigNumber)const;
	virtual bool operator == (int _number)const;
	
	virtual bool operator < (const BigNumber_t& _bigNumber)const;
	virtual bool operator > (const BigNumber_t& _bigNumber)const;
	virtual BigNumber_t operator + (BigNumber_t& _bigNumber);
	virtual BigNumber_t operator - (BigNumber_t& _bigNumber);
	void SetNumber(const char* _num);
	void SetNumber(const string& _num);

	const string& GetNumber()const{return m_num;}
	size_t NumberLength()const{return m_num.length();}
	int GetMin(size_t _first, size_t _sec);
	int GetMax(size_t _first, size_t _sec);
	
	protected:

	private:
	string m_num;
	int BorrowFunction(string& _number, int _index);
	
	};

	ostream& operator<<(ostream& os, const BigNumber_t& _number);
	istream& operator>>(istream& is, BigNumber_t& _number);
	
	
#endif //__BigNumber_H_
