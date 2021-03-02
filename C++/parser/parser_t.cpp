#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#include <parser_t.h>
#include <analyzer_t.h>


Parser_t::Parser_t (string _filename): m_ifs (_filename.data(), ifstream::in) 
{
	m_analyzer = new Analyzer_t();
}

Parser_t::~Parser_t() 
{
	m_ifs.close();
	if (m_analyzer)
	{
		delete m_analyzer;
		m_analyzer = NULL;
	}
}

void Parser_t::AnalyzeFile()
{
	string line;
	size_t lineNum = 0;
	
	while (m_ifs.good())
	{
		getline(m_ifs, line);
		++lineNum;
		m_analyzer->Set(line, lineNum);
		m_analyzer->AnalyzeLine();

	} 
	m_analyzer->CleanUp(lineNum);
}


