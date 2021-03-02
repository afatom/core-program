#ifndef __TEXCEPTION_T_H_
#define __TEXCEPTION_T_H_

#include <string>

using namespace std;

template <class T>
class TException_t{
	public:

	
	//CTOR-these parameters are passed by user!
	TException_t(const T& _obj,int _line ,const string& _file, const string& _func, const string& _msg)
	{
		m_object = _obj;
		m_lineNumber = _line;
		m_sourceFile = _file;
		m_exceptionMsg = _msg;	
		m_func = _func;	
	}
	
	
	
	~TException_t(){;}
	/*  TException_t(const TException_t& _obj);  
	 * No need for copy CTOR. 
	/compile generates and provide copy ctor. its good for our uses 
	/cause we dont have pointers and ref vars in data path*/
	
	const T&       GetObject()const{return this->m_object;}
	const string&  GetExceptionMsg(){return m_exceptionMsg;}
	int  GetLineNUmber(){return m_lineNumber;}
	const string&  GetFileName(){return m_sourceFile;}
	const string&  GetFunc(){return m_func;}
	
	protected:
	
	private:
	T m_object;
	int m_lineNumber;
	string m_sourceFile;
	string m_func;
	string m_exceptionMsg;

};


#endif //__TEXCEPTION_T_H_
