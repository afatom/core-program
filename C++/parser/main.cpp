#include <iostream>

#include <parser_t.h>


int main(int argc, char* argv[])
{
	string filename = "ParserFile.txt";

	Parser_t p(filename);

	p.AnalyzeFile();
	
    return 0;
}
