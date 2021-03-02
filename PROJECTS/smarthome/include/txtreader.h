#ifndef __TXT_READER_T_H_
#define __TXT_READER_T_H_

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ireader.h>
#include <agentconfig.h>
using namespace std;

class TxtReader_t : public IReader_t
{
	private:
	string 	 m_path; //including filename ex: /home/usr/shoko.txt
	ifstream m_ifs;
	TxtReader_t& operator = (const TxtReader_t&);
	TxtReader_t(const TxtReader_t&);
	bool StrProcessing(AgentConfig_t&, string&);
	
	public:
	TxtReader_t(const char*);
	~TxtReader_t(){m_ifs.close();} //close file obj
	virtual string ReadLine(); //read file line by line (stop on /n)
	virtual string ReadWord(); //read file word by word (stop on white space)	
	AgentConfig_t ReadSingleConfigSet(); //read file line by line
	const string& GetPath() const {return m_path;} 	
};

#endif //__TXT_READER_T_H_
