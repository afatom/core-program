#include "mu_test.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>



#define MAX_LINE_LENGTH 256
#define FILES_NUM 1
#define CDR_FILE_NAME "cdr.txt" /**no need for relative path. same dir*/
#define FILE_INDEX 0


UNIT(Parser_Full_Tx_Test)

	FILE* fp;
	char buffer[MAX_LINE_LENGTH];
	/*char* pfn = "../cdrs/cdr.txt";*/
	
	char* pfn = "cdr.txt";
	
	Channel* ch;
	
	Parser* par;
	
	/***channel create for test ***/

	fp = fopen(pfn,"r");
	ASSERT_THAT(fp!=NULL);
	fclose(fp);
	
	ch = ChannelCreate("MSGQQ123WE", 1024, CHANNEL_CREATE);
	par= ParserCreate(pfn,MAX_LINE_LENGTH ,ch);

	

	ParseAndSend(par);
	
	ParserDestroy(&par);
	

END_UNIT

/*****************************************************************************/
TEST_SUITE(Parser Test)

TEST(Parser_Full_Tx_Test)

END_SUITE
