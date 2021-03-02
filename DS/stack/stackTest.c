#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "vector.h"
#include "ADTDefs.h"
#include "mu_test.h"

/*****************************/ /*TEST 1*/ /*Create Test*/
UNIT(Create_Normal_Inputs_Test)
    Stack *ptr = NULL;
    ptr = StackCreate(10, 4);
    ASSERT_THAT( ptr != NULL);
    StackDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 2*/
UNIT(Create_Zero_Both_Inputs_Test)
    Stack *ptr = NULL;
    ptr = StackCreate(0, 0);
 	ASSERT_THAT( ptr == NULL);
    StackDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 3*/
UNIT(Create_Zero_Initial_Size_Test)
    Stack *ptr = NULL;
    ptr = StackCreate(0, 4);
 	ASSERT_THAT( ptr != NULL);
    StackDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 4*/
UNIT(Create_Zero_IncrBlock_Test)
	Stack *ptr = NULL;
    ptr = StackCreate(4, 0);
 	ASSERT_THAT( ptr != NULL);
    StackDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 5*/
UNIT(Create_Huge_Initial_Allocation_Test)
	Stack *ptr = NULL;
    ptr = StackCreate(123456789987456213, 5);
 	ASSERT_THAT( ptr == NULL);
    StackDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 6*/ /*Push Test*/
UNIT(Push_To_Null_Stack)
	Stack *ptr = NULL;
    ADTErr res;
	res = StackPush(ptr,5);
 	ASSERT_THAT(res == ERR_STACK_NOT_INITIALIZED);
    StackDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 7*/
UNIT(Push_One_Element_Tets)
    ADTErr res;
    Stack *ptr = NULL;
    ptr = StackCreate (3,3);
    res = StackPush(ptr, 5);
    ASSERT_THAT(res == ERR_OK);
    StackDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 8*/
UNIT(Push_Few_Elements_Test)
    ADTErr res;
    int i;
    Stack *ptr = NULL;
    ptr = StackCreate(10, 3);
    for (i=0; i<8; ++i)
    {
        res = StackPush(ptr, i+2);
    }
    ASSERT_THAT(res == ERR_OK);
    StackDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 9*/
UNIT(Push_Elements_After_Realloc_OP_Test)
    ADTErr res;
    int i;
    Stack *ptr = NULL;
    ptr = StackCreate(5, 5);
    for ( i = 0; i < 25; ++i)
    {
        res = StackPush(ptr, i);
    }
    ASSERT_THAT(res == ERR_OK);
    StackDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 10*/
UNIT(Push_Overflow_Test)
    ADTErr res;
    int i;
    Stack *ptr = NULL;
    ptr = StackCreate(10, 0);
    for ( i = 0; i < 13; ++i)
    {
        res = StackPush(ptr, i);
    }
    ASSERT_THAT(res == ERR_OVERFLOW);
    StackDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 11*/
UNIT(Push_With_InitialSize_Zero_Test)
    ADTErr res;
    int i;
    Stack *ptr = NULL;
    ptr = StackCreate(0, 10);
    for ( i = 0; i < 15; ++i)
    {
        res = StackPush(ptr, i);
    }
    ASSERT_THAT(res == ERR_OK);
    StackDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/

/*****************************/ /*TEST 13*/

/*****************************/ /*TEST 12*/
UNIT(Pop_Null_Test)
    Stack *ptr = NULL;
    ADTErr res;
    int noi = 0;
    res = StackPop(NULL, &noi);
    ASSERT_THAT(res == ERR_STACK_NOT_INITIALIZED);
    StackDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(Pop_Underflow_Test)
    int noi = 5;
    ADTErr res;
    Stack *ptr = NULL;
    ptr = StackCreate(10, 10);
    res = StackPop(ptr, &noi);
    ASSERT_THAT(res == ERR_UNDERFLOW);
    StackDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(Pop_One_Element_Test)
    int noi =222;
    ADTErr res;
    Stack *ptr = NULL;
    ptr = StackCreate(10, 10);
    StackPush(ptr, 1);
    StackPush(ptr, 2);
    StackPush(ptr, 1);
    StackPush(ptr, 4);
    res = StackPop(ptr, &noi);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(noi == 4);   
    StackDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(Pop_Few_Elements_Test)
    ADTErr res;
    int i, noi1 = 0, noi2 = 0, noi3 = 0, noi4 = 0;
    Stack *ptr = NULL;
    ptr = StackCreate(10, 10);
    {
    for(i = 0; i < 8; ++i)
        StackPush(ptr, i);
    }
    res = StackPop(ptr, &noi1);
    res = StackPop(ptr, &noi2);
    res = StackPop(ptr, &noi3);
    res = StackPop(ptr, &noi4);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(noi1 == 7);
    ASSERT_THAT(noi2 == 6);
    ASSERT_THAT(noi3 == 5);
    ASSERT_THAT(noi4 == 4);
    StackDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(Pop_With_Realloc_Test)
    ADTErr res;
    int noi1 = 0, i;
    Stack *ptr = NULL;
    ptr = StackCreate(10, 3);
    for (i = 0; i < 20; ++i)
    {
        StackPush(ptr, i);
    }
    for (i = 20; i > 5; --i)
    {
        res = StackPop(ptr, &noi1);
        ASSERT_THAT(res == ERR_OK);
        ASSERT_THAT(noi1 == i-1);
    }
    StackDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
/*****************************/ /*TEST 12*/
UNIT(StackTop_NULL_Ptr_Test)
    Stack *ptr = NULL;
    ADTErr res;
    int top = 0;
    res = StackTop(ptr, &top);
    ASSERT_THAT(res == ERR_STACK_NOT_INITIALIZED);
    StackDestroy(ptr);
END_UNIT

UNIT(StackTop_NULL_Item_Test)
    ADTErr res;
    Stack *ptr = NULL;
    ptr = StackCreate(10, 3);
    res = StackTop(ptr, NULL);
    ASSERT_THAT(res == ERR_STACK_GENERAL);
    StackDestroy(ptr);
END_UNIT

UNIT(StackTop_Empty_Stack_Test)
    ADTErr res;
    int top=0;
    Stack *ptr = NULL;
    ptr = StackCreate(10, 3);
    res = StackTop(ptr, &top);
    ASSERT_THAT(res == ERR_EMPTY_STACK);
    StackDestroy(ptr);
END_UNIT

UNIT(StackTop_Full_Stack_Test)
    int i;
    int top = 0;
    ADTErr res;
    Stack *ptr = NULL;
    ptr = StackCreate(10, 3);
    for (i=0; i<10; ++i)
    {
        StackPush(ptr,i+1);
    }
    res = StackTop(ptr, &top);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(top == 10);
    StackDestroy(ptr);
END_UNIT

/**********************************/
UNIT (Stack_Items_Num_Test)
    int noi;
    Stack *ptr = NULL;
    ptr = StackCreate(50, 20);
    ASSERT_THAT(ptr != NULL);
    StackPush(ptr,1);
    StackPush(ptr,1);
    StackPush(ptr,1);
    StackPush(ptr,1);
    StackItemsNum(ptr,&noi);
    ASSERT_THAT(noi == 4);
    StackDestroy(ptr);
END_UNIT

/*****************************/ /*TEST 12*/
UNIT(Massive_API_Stack_Use_Test)
    ADTErr PushRes, itemsNumRes, getRes, delRes;
    int i, j, noi = 0, get, delData; 
    Stack *ptr = NULL;
    ptr = StackCreate(1400, 200);
    ASSERT_THAT(ptr != NULL);
    /*for Push,set,get,itemsnum loop*/
    for (i = 0; i < 1500; ++i)
    {
        PushRes = StackPush(ptr,i+1);
        ASSERT_THAT (PushRes == ERR_OK);
        itemsNumRes = StackItemsNum(ptr,&noi);
        ASSERT_THAT(itemsNumRes == ERR_OK);
        ASSERT_THAT(noi == i+1);
        getRes = StackTop(ptr,&get);
        ASSERT_THAT(getRes == ERR_OK);
        ASSERT_THAT(get == i+1);
    }
    
    /*for Pop loop*/
    for (j=1500; j>0; --j)
    {
        delRes = StackPop(ptr, &delData);
        ASSERT_THAT(delRes == ERR_OK);
        ASSERT_THAT(delData == j);      
    }
    
    StackDestroy(ptr);
END_UNIT

/*Main function Macro*/
TEST_SUITE(_____Stack test__________________)

	TEST(Create_Normal_Inputs_Test)
	TEST(Create_Zero_Both_Inputs_Test)
	TEST(Create_Zero_Initial_Size_Test)
	TEST(Create_Zero_IncrBlock_Test)
	TEST(Create_Huge_Initial_Allocation_Test)
	TEST(Push_To_Null_Stack)
    TEST(Push_One_Element_Tets)
    TEST(Push_Few_Elements_Test)
    TEST(Push_Elements_After_Realloc_OP_Test)
    TEST(Push_Overflow_Test)
    TEST(Push_With_InitialSize_Zero_Test)
    TEST(Pop_Null_Test)
    TEST(Pop_Underflow_Test)
    TEST(Pop_One_Element_Test)
    TEST(Pop_Few_Elements_Test)
    TEST(Pop_With_Realloc_Test)
    TEST(StackTop_NULL_Ptr_Test)
    TEST(StackTop_NULL_Item_Test)
    TEST(StackTop_Empty_Stack_Test)
    TEST(StackTop_Full_Stack_Test)
    TEST(Massive_API_Stack_Use_Test)
    TEST(Stack_Items_Num_Test)

END_SUITE

