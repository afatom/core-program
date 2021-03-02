#ifndef __TOKENIZER_T_H_
#define __TOKENIZER_T_H_

#include <string>
#include <list>

using namespace std;

static const char delimiters[] = {'(',')','[',']','{','}',';','<','>','=','+','-','*','&'};

class Tokenizer_t 
{
	public:
		list<string>& operator() (string _line);
	private:
		list<string> m_tokens;
};
 
#endif /* __TOKENIZER_T_H_*/
 



 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
