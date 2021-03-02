#ifndef __IREADER_T_H_
#define __IREADER_T_H_

#include <string>

using namespace std;

class IReader_t{
	private:
	
	public:
	IReader_t(){}
	~IReader_t(){}
	
	virtual string ReadLine() = 0; //read file line by line (stop on /n)
	virtual string ReadWord() = 0; //read file word by word (stop on white space)
		
	};





#endif //__IREADER_T_H_
