#include "readerManager.h"
#include "watcher.h"
#include <stdlib.h>
#include <stdio.h>
#include "mu_test.h"


UNIT(ReaderManager_Create_And_Destroy_Test)
	
	ReaderManager* ptr=NULL;
	ptr = ReaderManagerCreate("../config/config.txt");
	
	ASSERT_THAT(ptr != NULL);
	ReaderManagerDestroy(&ptr);
	ASSERT_THAT(ptr==NULL);
END_UNIT


/**
 * This Test involves watcher,parser,cdr,channel and the whole chain*/
UNIT(ReaderManager_MP_Send_Test)
	
	ReaderManager* ptr=NULL;
	ptr = ReaderManagerCreate("../config/config.txt");
	
	ASSERT_THAT(ptr != NULL);
	
	ASSERT_THAT(ReaderManagerStart(ptr) == READERMANAGER_SUCCESS);
	ReaderManagerDestroy(&ptr);
	ASSERT_THAT(ptr==NULL);
END_UNIT




TEST_SUITE(ReaderManager Module Test)

	TEST(ReaderManager_Create_And_Destroy_Test)
	TEST(ReaderManager_MP_Send_Test)
END_SUITE

