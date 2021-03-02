#include <iostream>
#include <sstream>
#include <string>
#include <list>

#include <tokenizer_t.h>
#include <bits/stdc++.h>
using namespace std;

list<string>& Tokenizer_t::operator() (string _line)
{
	//making the string a stream	
	stringstream buffer(_line);
	string word, token;
	size_t pos=0, pos2=0, length=0, start=0;
	m_tokens.clear();
	
	while (buffer >> word) 
	{	
		// Find delimeter
		pos = word.find_first_of(delimiters); 
		
		// No delimiters -> push word and get another
		if (pos == string::npos)	
		{
			m_tokens.push_back(word);
			continue;
		}
		
		start = 0;
		pos2 = 0;
		while (pos != string::npos)
		{	
			// get token
			token = word.substr (start,pos-pos2); 
			
			// there is a token before the delimiter
			if(!token.empty()) 
			{
				m_tokens.push_back(token); 
			}
			
			pos2 = word.find_first_not_of (word[pos], pos);

			if(pos2==string::npos)
			{
				pos2 = word.length();
			}

			length = pos2-pos;
			
			// get delimiter ( +, { ) or several delimiters ( ++, }}} )
			token = word.substr (pos,length); 
			m_tokens.push_back(token);
			
			start = pos2;
			pos = word.find_first_of(delimiters, start);
		}
		
		if (start < word.length()) m_tokens.push_back(word.substr(start));
				
	}
	return m_tokens;
}

 



 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
