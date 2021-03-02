#include <txtreader.h>
#include <fstream>
#include <iostream>
#include <exception>
using namespace std;



TxtReader_t::TxtReader_t(const char* _filePath)
{
	m_path = _filePath;
	m_ifs.open(_filePath, std::ifstream::in); //this func can throw (exception& e)
}


string TxtReader_t::ReadLine() //read file line by line (stop on /n)
{
	string line; 
	std::getline(m_ifs, line);
	return line;
}

string TxtReader_t::ReadWord() //read file line by line (stop on /n)
{
	string word; 
	m_ifs >> word;
	return word;
}


bool TxtReader_t::StrProcessing(AgentConfig_t& _agentConfObj, string& _line)
{
	size_t f=0,e=0;
	if(!(f = _line.find_first_of("["))) //match
	{
		e = _line.find_first_of("]");
	
		_agentConfObj.SetId(_line.substr(f+1, e-f-1));
		return false;
	}
	
	if(!_line.find("type")) //match
	{
		_agentConfObj.SetType(_line.substr(7));
		return false;
	}
	
	if(!_line.find("room")) //match
	{
		_agentConfObj.SetRoom(_line.substr(7));
		return false;
	}
	
	if(!_line.find("floor")) //match
	{
		_agentConfObj.SetFloor(_line.substr(8));
		return false;
	}
	
	if(!_line.find("log")) //match
	{
		_agentConfObj.SetLog(_line.substr(6));
		return false;
	}
	
	if(!_line.find("config")) //match
	{
		_agentConfObj.SetConfig(_line.substr(9));
		return true;
	}
}
	




AgentConfig_t TxtReader_t::ReadSingleConfigSet() //read file line by line 	
{
	AgentConfig_t conf;
	string fId = "0";
	conf.SetId(fId);
	string line;
	while(std::getline(m_ifs, line))
	{
		if(StrProcessing(conf, line)){ //if first word is config
			break;
		}
	}
	
    return conf;
}
