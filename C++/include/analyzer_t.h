#ifndef __ANALYZER_T_H_
#define __ANALYZER_T_H_

#include <iostream>
#include <string>
#include <list>
#include <bitset>
#include <set>

#include <tokenizer_t.h>

using namespace std;


static const string types[] = {"char","short","int","long","float","double","void"};
static const string operators[] = {"++","--","==","->","=","+","-","*","&","<<",">>"};
static const string keyWords[] = {"if","else","for","while","class","private","public","protected","main","const","virtual"};

class Analyzer_t 
{
	public:
	Analyzer_t();	
	~Analyzer_t();
					
	void Set(string _line, size_t _lineNum);
	void PrintLine();
	void PrintError(string _err);
	void AnalyzeLine();
	void CleanUp(size_t _lineNum);

	private:
	list<string>* m_tokens;
	size_t m_lineNum;
	Tokenizer_t m_Tokenizer;

	const set<string> tokensSet;
	const set<string> keywordsSet;
	const set<string> operatorsSet;
	const set<char> delimitersSet;
	
	set<string> m_symbols;
	
	int m_parentheses; 		// '(', ')'
	int m_brackets; 			// '[', ']'
	int m_braces; 			// '{', '}'
	int m_nIf;				//number of if's
	
	bitset<6> m_flags; 
	void AnalyzeToken(string& _token);

	
	// flags coresponding to the type of the last token: 0. type, 1. key-word, 2. operator, 3. delimiter, 4.user-defined, 5.number

};

 #endif /* __ANALYZER_T_H_*/
