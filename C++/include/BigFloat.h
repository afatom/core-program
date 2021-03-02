#ifndef __BIG_FLOAT_T_H_
#define __BIG_FLOAT_T_H_
#include <BigNumber.h>
#include <string>
using namespace std;

class BigFloat_t : public BigNumber_t {
	public:
	virtual ~BigFloat_t(){return;}
	BigFloat_t();
	BigFloat_t(const char* _number);
	//BigFloat_t(float _number);
	BigFloat_t(const string _number);
	BigFloat_t(BigFloat_t& _bigNumber); //copy CTOR
	
	BigFloat_t& operator = (const BigFloat_t& _bigNumber);
	//BigFloat_t& operator = (float _number);

	//virtual bool operator == (float _number)const{return true;}
	
	virtual BigFloat_t operator + (BigFloat_t& _bigNumber);
	virtual BigFloat_t operator - (BigFloat_t& _bigNumber);
	
	protected:

	private:

	};

	
	
#endif //__BIG_FLOAT_T_H_
