#ifndef __PARSER_T_H_
#define __PARSER_T_H_

#include <fstream>
#include <iostream>
#include <string>

#include <analyzer_t.h>

using namespace std;


class Parser_t 
{
	public:
		Parser_t (string _filename);
		
		virtual ~Parser_t();
			
		virtual void AnalyzeFile();

	private:
		ifstream m_ifs;
		Analyzer_t* m_analyzer;	
		
		
 };
 
 #endif /* __PARSER_T_H_*/

