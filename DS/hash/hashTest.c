#include "hash.h"
#include<stdlib.h>
#include<stdio.h>
#include "mu_test.h"
#include <time.h>

UNIT(Hash_Create_And_Destroy_Test)
    Hash* ptr = NULL; 
    ptr = HashCreate(5);
    ASSERT_THAT(NULL != ptr);
    HashDestroy(ptr);
END_UNIT

UNIT(Hash_Create_And_Destroy_Null_Test)
    Hash* ptr = NULL; 
    ASSERT_THAT(NULL == ptr);
    HashDestroy(ptr);
END_UNIT

UNIT(Hash_Double_Destroy_Test)
    Hash* ptr = NULL; 
    ptr = HashCreate(5);
    ASSERT_THAT(NULL != ptr);
    HashDestroy(ptr);
    HashDestroy(ptr);
END_UNIT



UNIT(Hash_ItemsNum_Test)
    ADTErr status;
  
    Hash* ptr = NULL; 
    ptr = HashCreate(20);
    ASSERT_THAT(NULL != ptr);
    ASSERT_THAT((status =HashInsert(ptr, 0)) == ERR_INVALID_DATA);
    ASSERT_THAT((status =HashInsert(ptr, -1)) == ERR_INVALID_DATA);
    ASSERT_THAT((HashNumOfItems(ptr)) == 0);
    ASSERT_THAT((status =HashInsert(ptr, 5)) == ERR_OK);
    ASSERT_THAT((status =HashInsert(ptr, 8)) == ERR_OK);
    ASSERT_THAT((status =HashInsert(ptr, 20)) == ERR_OK);
    ASSERT_THAT((status =HashInsert(ptr, 40)) == ERR_OK);
    ASSERT_THAT((status = HashInsert(ptr, 88)) == ERR_OK);
    ASSERT_THAT((status = HashInsert(ptr, 99)) == ERR_OK);
    ASSERT_THAT((status = HashInsert(ptr, 100)) == ERR_OK);
    ASSERT_THAT((status = HashInsert(ptr, 450)) == ERR_OK);
    ASSERT_THAT((HashNumOfItems(ptr))==8);
    
    HashDestroy(ptr);
END_UNIT


UNIT(Hash_Insert_Test)
    ADTErr status;
  
    Hash* ptr = NULL;
    ASSERT_THAT((HashNumOfItems(ptr)) == 0);
    ptr = HashCreate(20);
    ASSERT_THAT(NULL != ptr);
    ASSERT_THAT((HashNumOfItems(ptr)) == 0);
    ASSERT_THAT((status =HashInsert(ptr, 0)) == ERR_INVALID_DATA);
    ASSERT_THAT((status =HashInsert(ptr, -1)) == ERR_INVALID_DATA);
    ASSERT_THAT((status =HashInsert(ptr, 5)) == ERR_OK);
    ASSERT_THAT((status =HashInsert(ptr, 5)) == ERR_DATA_EXIST);
    ASSERT_THAT((status =HashInsert(ptr, 8)) == ERR_OK);
    ASSERT_THAT((status =HashInsert(ptr, 20)) == ERR_OK);
    ASSERT_THAT((status =HashInsert(ptr, 40)) == ERR_OK);
    
    ASSERT_THAT((HashNumOfItems(ptr))==4);
    
    
    HashDestroy(ptr);
END_UNIT

UNIT(Hash_Is_Found_Main_Test)
ADTErr status;
Hash *ptr = NULL;
ASSERT_THAT( HashIsFound(ptr, 1) == 0);
ptr = HashCreate(20);
ASSERT_THAT(NULL != ptr);
ASSERT_THAT((status = HashInsert(ptr, 5)) == ERR_OK);
ASSERT_THAT((status = HashInsert(ptr, 5)) == ERR_DATA_EXIST);
ASSERT_THAT((status = HashInsert(ptr, 8)) == ERR_OK);
ASSERT_THAT((status = HashInsert(ptr, 20)) == ERR_OK);
ASSERT_THAT((status = HashInsert(ptr, 40)) == ERR_OK);

ASSERT_THAT(HashIsFound(ptr, 5) == 1);

ASSERT_THAT(HashIsFound(ptr, 545) == 0);
ASSERT_THAT(HashIsFound(ptr, 20) == 1);
ASSERT_THAT(HashIsFound(ptr, 40) == 1);
ASSERT_THAT(HashIsFound(ptr, 8) == 1);
HashDestroy(ptr);
END_UNIT

UNIT(Hash_Insert_Overflow_Test)
ADTErr status;
Hash *ptr = NULL;
ASSERT_THAT(HashIsFound(ptr, 1) == 0);
ptr = HashCreate(4);
ASSERT_THAT(NULL != ptr);
ASSERT_THAT((status = HashInsert(ptr, 5)) == ERR_OK);
ASSERT_THAT((status = HashInsert(ptr, 5)) == ERR_DATA_EXIST);
ASSERT_THAT((status = HashInsert(ptr, 8)) == ERR_OK);
ASSERT_THAT((status = HashInsert(ptr, 20)) == ERR_OK);
ASSERT_THAT((status = HashInsert(ptr, 40)) == ERR_OK);
ASSERT_THAT((status = HashInsert(ptr, 409)) == ERR_OVERFLOW);
ASSERT_THAT((status = HashInsert(ptr, 489)) == ERR_OVERFLOW);
HashDestroy(ptr);
END_UNIT

UNIT(Hash_Insert_Invalid_Data_Test)
ADTErr status;
Hash *ptr = NULL;
ASSERT_THAT(HashIsFound(ptr, 1) == 0);
ptr = HashCreate(20);
ASSERT_THAT(NULL != ptr);
ASSERT_THAT((status = HashInsert(ptr, 5)) == ERR_OK);
ASSERT_THAT((status = HashInsert(ptr, 5)) == ERR_DATA_EXIST);
ASSERT_THAT((status = HashInsert(ptr, 8)) == ERR_OK);
ASSERT_THAT((status = HashInsert(ptr, 20)) == ERR_OK);
ASSERT_THAT((status = HashInsert(ptr, 0)) == ERR_INVALID_DATA);
ASSERT_THAT((status = HashInsert(ptr, -1)) == ERR_INVALID_DATA);
ASSERT_THAT((status = HashInsert(ptr, 489)) == ERR_OK);
HashDestroy(ptr);
END_UNIT

UNIT(Hash_Insert_To_Null_Hash_Test)
ADTErr status;
Hash *ptr = NULL;
ASSERT_THAT(HashIsFound(ptr, 1) == 0);

ASSERT_THAT((status = HashInsert(ptr, 5)) == ERR_NOT_INITIALIZED);
ASSERT_THAT((status = HashInsert(ptr, 4)) == ERR_NOT_INITIALIZED);

END_UNIT

UNIT(Hash_Insertion_Logic_Test)

END_UNIT

UNIT(Hash_Remove_From_Empty_Hash_Test)
ADTErr status;
Hash *ptr = NULL;
ASSERT_THAT((status = HashRemove(ptr, 5)) == ERR_NOT_INITIALIZED);
ptr = HashCreate(20);
ASSERT_THAT(NULL != ptr);
ASSERT_THAT((status = HashRemove(ptr, 5)) == ERR_UNDERFLOW);
HashDestroy(ptr);
END_UNIT

UNIT(Hash_Remove_Normal_Test)
ADTErr status;
Hash *ptr = NULL;
ASSERT_THAT(HashIsFound(ptr, 1) == 0);
ptr = HashCreate(20);
ASSERT_THAT(NULL != ptr);
ASSERT_THAT((status = HashInsert(ptr, 5)) == ERR_OK);
ASSERT_THAT((status = HashRemove(ptr, 5)) == ERR_OK);
HashDestroy(ptr);
END_UNIT

UNIT(Hash_Remove_Invalid_Data_Test)
ADTErr status;
Hash *ptr = NULL;
ASSERT_THAT(HashIsFound(ptr, 1) == 0);
ptr = HashCreate(20);
ASSERT_THAT(NULL != ptr);
ASSERT_THAT((status = HashInsert(ptr, 5)) == ERR_OK);
ASSERT_THAT((status = HashInsert(ptr, 10)) == ERR_OK);
ASSERT_THAT((status = HashInsert(ptr, 15)) == ERR_OK);
ASSERT_THAT((status = HashRemove(ptr, -1)) == ERR_INVALID_DATA);
ASSERT_THAT((status = HashRemove(ptr, 0)) == ERR_INVALID_DATA);
HashDestroy(ptr);
END_UNIT


UNIT(Hash_Remove_Unexist_Data_Test)
ADTErr status;
Hash *ptr = NULL;
ASSERT_THAT(HashIsFound(ptr, 1) == 0);
ptr = HashCreate(20);
ASSERT_THAT(NULL != ptr);
ASSERT_THAT((status = HashInsert(ptr, 5)) == ERR_OK);
ASSERT_THAT((status = HashInsert(ptr, 10)) == ERR_OK);
ASSERT_THAT((status = HashInsert(ptr, 15)) == ERR_OK);
ASSERT_THAT((status = HashRemove(ptr, 99)) == ERR_DATA_DOES_NOT_EXIST);
ASSERT_THAT((status = HashRemove(ptr, 5)) == ERR_OK);
ASSERT_THAT((status = HashRemove(ptr, 8)) == ERR_DATA_DOES_NOT_EXIST);
/*
*/
HashDestroy(ptr);
END_UNIT

UNIT(Hash_Removing_Logic_Data_Test)

END_UNIT

UNIT(Hash_Test_Random_Test)
Hash *ptr = NULL;
ptr = HashCreate(1010);

/*
srand((unsigned)time(NULL));
for (i =0; i<100; ++i)
{
    num = rand()%1000;
   
}
avg = HashAverageCollisions(ptr);
maxCol =  HashMaxCollisions(ptr);
printf("Max Collisions = %lu\n", maxCol);
printf("avg Collisions = %f\n", avg);
HashPrint(ptr);
*/
HashDestroy(ptr);
END_UNIT
/************************************************/
TEST_SUITE(Hash Test)
    TEST(Hash_Create_And_Destroy_Test)
    TEST(Hash_Create_And_Destroy_Null_Test)
    TEST(Hash_Double_Destroy_Test)
    TEST(Hash_Insert_Test)
    TEST(Hash_ItemsNum_Test)
    TEST(Hash_Is_Found_Main_Test)
    TEST(Hash_Insert_Overflow_Test)
    TEST(Hash_Insert_Invalid_Data_Test)
    TEST(Hash_Insert_To_Null_Hash_Test)
    TEST(Hash_Remove_From_Empty_Hash_Test)
    TEST(Hash_Remove_Normal_Test)
    
    TEST(Hash_Remove_Invalid_Data_Test)
    TEST(Hash_Remove_Unexist_Data_Test)

    /*TEST(Hash_Test_Random_Test)*/
END_SUITE
