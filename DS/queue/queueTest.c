#include "queue.h"
#include <stdlib.h>  /*size_t*/
#include <stdio.h>
#include "ADTDefs.h"
#include "mu_test.h"

/*****************************/ /*TEST 1*/ /*Create Test*/
UNIT(Create_Normal_Inputs_Test)
    Queue *ptr = NULL;
    ptr = QueueCreate(4);
    ASSERT_THAT( ptr != NULL);
    QueueDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 2*/
UNIT(Create_Zero_Input_Test)
    Queue *ptr = NULL;
    ptr = QueueCreate(0);
 	ASSERT_THAT( ptr == NULL);
    QueueDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 5*/
UNIT(Create_Huge_Initial_Allocation_Test)
	Queue *ptr = NULL;
    ptr = QueueCreate(123456789987456213);
 	ASSERT_THAT( ptr == NULL);
    QueueDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 6*/ /*Insert Test*/
UNIT(Insert_To_Null_Queue)
	Queue *ptr = NULL;
    ADTErr res;
	res = QueueInsert(ptr,5);
 	ASSERT_THAT(res == ERR_NOT_INITIALIZED);
    QueueDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 7*/
UNIT(Insert_One_Element_Tets)
    ADTErr res;
    Queue *ptr = NULL;
    ptr = QueueCreate (3);
    res = QueueInsert(ptr, 5);
    ASSERT_THAT(res == ERR_OK);
    QueueDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 8*/
UNIT(Insert_Few_Elements_Test)
    ADTErr res;
    int i;
    Queue *ptr = NULL;
    ptr = QueueCreate(10);
    for (i=0; i<8; ++i)
    {
        res = QueueInsert(ptr, i+2);
    }
    ASSERT_THAT(res == ERR_OK);
    QueueDestroy(ptr);
END_UNIT

/*****************************/ /*TEST 10*/
UNIT(Insert_Overflow_Test)
    Queue *ptr = NULL;
    int i = 0;
    ADTErr res;
    ptr = QueueCreate(10);
    for (i=0; i < 13; ++i)
    {
        res = QueueInsert(ptr, i);
    }
    ASSERT_THAT(res == ERR_OVERFLOW);
    QueueDestroy(ptr);
END_UNIT

/*****************************/ /*TEST 13*/
/*
UNIT(ItemsNum_Counting_Test)
    Queue *ptr = NULL;
    ADTErr res;
    int noi = 0;
    int i = 0;
    ptr = QueueCreate(10, 10);
    for (i=0; i < 7; ++i)
    {
        res = QueueInsert(ptr, i);
    }
    res = QueueItemsNum(ptr, &noi);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(noi == 7);
    QueueDestroy(ptr);
END_UNIT
*/
/*****************************/ /*TEST 12*/
UNIT(Remove_Null_Test)
    Queue *ptr = NULL;
    ADTErr res;
    int noi = 0;
    res = QueueRemove(NULL, &noi);
    ASSERT_THAT(res == ERR_NOT_INITIALIZED);
    QueueDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(Remove_Underflow_Test)
    Queue *ptr = NULL;
    int noi = 5;
    ADTErr res;
    ptr = QueueCreate(10);
    res = QueueRemove(ptr, &noi);
    ASSERT_THAT(res == ERR_UNDERFLOW);
    /*QueueItemsNum(ptr, &noi);
    ASSERT_THAT(noi == 0);*/
    QueueDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(Remove_One_Element_Test)
    Queue *ptr = NULL;
    ADTErr res;
    int noi =222;
    ptr = QueueCreate(10);
    QueueInsert(ptr, 213);
    QueueInsert(ptr, 2);
    QueueInsert(ptr, 1);
    QueueInsert(ptr, 4);
    res = QueueRemove(ptr, &noi);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(noi == 213);   
    /*QueueItemsNum(ptr, &nom);
    ASSERT_THAT(nom == 3);*/
    QueueDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(Remove_Few_Elements_Test)
    Queue *ptr = NULL;
    ADTErr res;
    int noi1 = 0, noi2=0, noi3=0, noi4=0, i=0;
    ptr = QueueCreate(10);
    for (i=0; i<8; ++i)
    {
        QueueInsert(ptr, i);
    }
    res = QueueRemove(ptr, &noi1);
    res = QueueRemove(ptr, &noi2);
    res = QueueRemove(ptr, &noi3);
    res = QueueRemove(ptr, &noi4);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(noi1 == 0);
    ASSERT_THAT(noi2 == 1);
    ASSERT_THAT(noi3 == 2);
    ASSERT_THAT(noi4 == 3);
    QueueDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(Remove_Many_Elements_Test)
    Queue *ptr = NULL;
    ADTErr res;
    size_t nom;
    int noi1 = 0, i=0, j=20;
    ptr = QueueCreate(20);
    for (i=0; i < 20; ++i)
    {
        QueueInsert(ptr, i+1);
    }
    ASSERT_THAT(QueueItemsNum(ptr, &nom)==ERR_OK);
    ASSERT_THAT(nom == 20);
    for (j=0; j < 20; ++j)
    {
        res = QueueRemove(ptr, &noi1);
        ASSERT_THAT(res == ERR_OK);
        ASSERT_THAT(noi1 == j+1);
        
    }
    ASSERT_THAT(QueueItemsNum(ptr, &nom) == ERR_OK);
    ASSERT_THAT(nom == 0);
    QueueDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/

/*****************************/ /*TEST 12*/

UNIT(Massive_API_Queue_Use_Test)
    Queue *ptr = NULL;
    ADTErr InsertRes, itemsNumRes, delRes;
    int i=0, j=299, delData = 0;
    size_t nom;
    ptr = QueueCreate(500);
    

    for (i=0; i < 300; ++i)
    {
        InsertRes = QueueInsert(ptr,i+1);
        ASSERT_THAT (InsertRes == ERR_OK);
        itemsNumRes = QueueItemsNum(ptr, &nom);
        ASSERT_THAT(itemsNumRes == ERR_OK);
        ASSERT_THAT(nom == i+1);
    }
    
    /*for Remove loop*/
    
    for (j=0; j>1; --j)
    {
        delRes = QueueRemove(ptr, &delData);
        ASSERT_THAT(delRes == ERR_OK);
        ASSERT_THAT (delData == j+2);
    }
    
    QueueDestroy(ptr);
END_UNIT

/*Main function Macro*/
TEST_SUITE(Queue test)
    TEST(Create_Normal_Inputs_Test)
    TEST(Create_Zero_Input_Test)
    TEST(Create_Huge_Initial_Allocation_Test)
    TEST(Insert_To_Null_Queue)
    TEST(Insert_One_Element_Tets)
    TEST(Insert_Few_Elements_Test)
    TEST(Insert_Overflow_Test)
    TEST(Remove_Null_Test)
    TEST(Remove_Underflow_Test)
    TEST(Remove_One_Element_Test)
    TEST(Remove_Few_Elements_Test)
    TEST(Remove_Many_Elements_Test)
    TEST(Massive_API_Queue_Use_Test)
END_SUITE