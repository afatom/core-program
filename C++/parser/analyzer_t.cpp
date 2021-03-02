#include <iostream>
#include <string>
#include <list>
#include <bitset>
#include <set>

#include <analyzer_t.h>
#include <tokenizer_t.h>

using namespace std;

Analyzer_t::Analyzer_t() :  tokensSet( types, types + (sizeof(types)/sizeof(types[0])) ), 
							keywordsSet( keyWords, keyWords + (sizeof(keyWords)/sizeof(keyWords[0]))), 
							operatorsSet( operators, operators + (sizeof(operators)/sizeof(operators[0]))), 
							delimitersSet( delimiters, delimiters + (sizeof(delimiters)/sizeof(delimiters[0])))
{
	m_parentheses=0;
	m_brackets=0;
	m_braces=0;
	m_nIf=0; 
	m_flags.reset();
	m_symbols.clear();
}
		
Analyzer_t::~Analyzer_t(){}
				
void Analyzer_t::Set(string _line, size_t _lineNum)
{
	m_tokens = &m_Tokenizer(_line);
	m_lineNum = _lineNum;
}
				
void Analyzer_t::PrintLine()
{
	cout << endl << "LINE " << m_lineNum << " : " << endl;
	for(typename list<string>::iterator it = m_tokens->begin(); it != m_tokens->end(); ++it)
	{
		cout << "\"" << *it << "\" ";
	}
	cout << endl;
}
		       
void Analyzer_t::PrintError(string _err)
{
	cout << "LINE" << m_lineNum << ": " << _err << endl;
}
		
void Analyzer_t::AnalyzeToken(string& _token)
{
	int tokenType = 4;
	
	// 1st token is not "main"
	if(m_flags.none() && _token != "main")	
		{PrintError("Error - has to start with \"main\""); }	
				
	// the token is predefined type
	if(tokensSet.find(_token) != tokensSet.end()) 
	{
		tokenType = 0; 
		
		// previous token is predefined type -> Error
		if(m_flags[0]) 				
		{PrintError("Error - \"" + _token + "\" can not name a variable");}	
	}	

	// the token is predefined keyWord
	else if (keywordsSet.find(_token) != keywordsSet.end()) 	
	{
		tokenType = 1;

		// previous token is predefined type -> Error	
		if(m_flags[0]) 				
		{PrintError("Error - \"" + _token + "\" multiple type declaration");}

		if(_token == "if") 
			{++m_nIf;}
		
		if (_token == "else") 	
		{
			--m_nIf;
			if(m_nIf < 0)
			{
				m_nIf = 0;
				PrintError ("Error - \"else\" without \"if\"");
			}
		}
		
	}	
	// the token is predefined operator
	else if (operatorsSet.find(_token) != operatorsSet.end()) 
	{
		tokenType = 2; 
		
		if(m_flags[0]) // previous token is predefined type -> Error
		{PrintError("Error - \"" + _token + "\" can not name a variable");}
	}	

	// The token is a single or multiple predefined delimiter
	else if (delimitersSet.find(_token[0]) != delimitersSet.end()) 
	{
		tokenType = 3;
		
		// Previous token is predefined type -> Error
		if(m_flags[0]) 
		{PrintError("Error - \"" + _token + "\" can not name a variable");}

		if(_token.length() > 2) 
		{
			if (_token[0] == '+' || _token[0] == '-' )
			{PrintError ("Error - illegal operator \"" + _token + "\"");}
		}	
		
		if(_token[0] == '(') 
			{m_parentheses += (int)_token.length();}
		if(_token[0] == ')') 
		{
			m_parentheses -= (int)_token.length();
			for ( ;m_parentheses < 0; ++m_parentheses)
				{PrintError ("Error - \")\" without \"(\" ");}
		}	
		
		if(_token[0] == '[') 
			{m_brackets += (int)_token.length();}		
		if(_token[0] == ']') 
		{
			m_brackets -= (int)_token.length();
			for ( ;m_brackets < 0; ++m_brackets)
				{PrintError ("Error - \"]\" without \"[\" ");}					
		}	
		
		if(_token[0] == '{') 
			{m_braces += (int)_token.length();}						
		if(_token[0] == '}') 
		{
			m_braces -= (int)_token.length();
			for ( ;m_braces < 0; ++m_braces)
				{PrintError ("Error - \"}\" without \"{\" ");}					
		}	
	}	
	
	// the token is user-defined
	else if(_token[0] < '0' || _token[0] > '9') 
	{
		tokenType = 4;
		
		// if found in m_symbols
		if (m_symbols.find(_token) != m_symbols.end()) 
		{
			// if previous token is predefined type -> Error - already declared
			if(m_flags[0]) 
			{PrintError("Error - variable \"" + _token + "\" already declared");}
		}
		
		// if not found in m_symbols	
		else 
		{	// if previous token is predefined type
			if(m_flags[0]) 
				// insert to m_symbols
				{m_symbols.insert(_token); } 
			// if previous token is not predefined type -> Error - Not declared
			else 
			{
				PrintError("Error -  \"" + _token + "\" not declared");						
			}
		}
	}
	// the token is a number (most probably)
	else 
	{
		tokenType = 5;
		
		// previous token is predefined type -> Error
		if(m_flags[0]) 
		{PrintError("Error - \"" + _token + "\" can not name a variable");}				
	}
	
	m_flags.reset();	
	m_flags[tokenType] = 1;	// set the right flag
}

void Analyzer_t::AnalyzeLine()
{
	for(typename list<string>::iterator it = m_tokens->begin(); it != m_tokens->end(); ++it)
	{
		AnalyzeToken(*it);
	}
}        
// Cleanup the remaind opening parentheses, brackets and braces
void Analyzer_t::CleanUp(size_t _lineNum)
{
	m_lineNum = _lineNum;
	if(m_parentheses > 0) 
		{cout << "LINE" << m_lineNum << ": Error -  " << m_parentheses << " opening parentheses \"(\" left" << endl;}
		
	if(m_brackets > 0) 
		{cout << "LINE" << m_lineNum << ": Error -  " << m_brackets << " opening brackets \"[\" left" << endl;}

	if(m_braces > 0) 
		{cout << "LINE" << m_lineNum << ": Error -  " << m_braces << " opening braces \"{\" left" << endl;}
}	

