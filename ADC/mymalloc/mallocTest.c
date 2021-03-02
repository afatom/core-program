#include <stdio.h>
#include "mmalloc.h"
#include <stdlib.h> /*malloc*/
#include <assert.h>
#include "mu_test.h"



#define BUFF_SIZE 16
#define BUUFS_NUM 1024



UNIT(My_Malloc_Create_And_Destroy_Test)
	Pool* pool = NULL; 
	pool = MmallocCreate(BUFF_SIZE, BUUFS_NUM);
	ASSERT_THAT(pool != NULL);
	MmallocDestroy(&pool);
	ASSERT_THAT(pool == NULL);
END_UNIT


UNIT(My_Malloc_Allocate_And_Free_Test)
	Pool* pool = NULL; 
	void* ptr1 = NULL; 
	pool = MmallocCreate(BUFF_SIZE, BUUFS_NUM);
	ASSERT_THAT(pool != NULL);
	
	ptr1 = MyMalloc(pool);
	ASSERT_THAT(ptr1 != NULL);
	ASSERT_THAT(FreeBufsNum(pool) == BUUFS_NUM-1);
	
	MyFree(pool, ptr1);
	ASSERT_THAT(FreeBufsNum(pool) == BUUFS_NUM);
	
	MmallocDestroy(&pool);
	ASSERT_THAT(pool == NULL);
END_UNIT


UNIT(My_Malloc_Allocate_And_Usage_Free_Test)
	Pool* pool = NULL; 
	void* ptr1 = NULL;
	void* ptr2 = NULL;
	void* ptr3 = NULL;
	 
	pool = MmallocCreate(BUFF_SIZE, BUUFS_NUM);
	ASSERT_THAT(pool != NULL);
	
	ptr1 = MyMalloc(pool);
	ASSERT_THAT(ptr1 != NULL);
	ASSERT_THAT(FreeBufsNum(pool) == BUUFS_NUM-1);
	
	
	ptr2 = MyMalloc(pool);
	ASSERT_THAT(ptr2 != NULL);
	ASSERT_THAT(FreeBufsNum(pool) == BUUFS_NUM-2);
	
	
	ptr3 = MyMalloc(pool);
	ASSERT_THAT(ptr3 != NULL);
	ASSERT_THAT(FreeBufsNum(pool) == BUUFS_NUM-3);
	
	*(char*)ptr1 = 'A';
	*(char*)ptr2 = '9';
	*(char*)ptr3 = 'Q';
	
	ASSERT_THAT(*(char*)ptr1 == 'A');
	ASSERT_THAT(*(char*)ptr2 == '9');
	ASSERT_THAT(*(char*)ptr3 == 'Q');
	
	MyFree(pool, ptr1);
	MyFree(pool, ptr2);
	MyFree(pool, ptr3);
	ASSERT_THAT(FreeBufsNum(pool) == BUUFS_NUM);
	
	MmallocDestroy(&pool);
	ASSERT_THAT(pool == NULL);
END_UNIT


/******************************************************************************************************/
/*Main function Macro*/
TEST_SUITE(My Malloc Unit Tests)
TEST(My_Malloc_Create_And_Destroy_Test)
TEST(My_Malloc_Allocate_And_Free_Test)
TEST(My_Malloc_Allocate_And_Usage_Free_Test)
END_SUITE
