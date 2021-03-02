#include "mu_test.h"
#include "dataManager.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/*

UNIT(DataManager_Create_Test)
	DataManager* dmp1 = NULL;

	dmp1 = DataManagerCreate("../config/config.txt");
	ASSERT_THAT(dmp1 != NULL);
	DataManagerDestroy(&dmp1);
	ASSERT_THAT(dmp1==NULL);
END_UNIT

*/


UNIT(DataManager_Destroy_Test)
	DataManager* dmp = NULL;
	/*relative path of config file */
	dmp = DataManagerCreate("../config/config.txt");
	ASSERT_THAT(dmp != NULL);
	
	DataManagerDestroy(&dmp);
	ASSERT_THAT(dmp==NULL);
END_UNIT



UNIT(DataManager_Receive_Test)
	DataManager* dmp = NULL;
	/*relative path of config file */
	dmp = DataManagerCreate("../config/config.txt");
	ASSERT_THAT(dmp != NULL);
	
	ASSERT_THAT((DataManagerRun(dmp)) == DATAMANAGER_SUCCESS);
	
	DataManagerDestroy(&dmp);
	ASSERT_THAT(dmp==NULL);
END_UNIT

TEST_SUITE(DataManager Module Test)

	/*TEST(DataManager_Create_Test)*/
	TEST(DataManager_Destroy_Test)
	TEST(DataManager_Receive_Test)
END_SUITE
