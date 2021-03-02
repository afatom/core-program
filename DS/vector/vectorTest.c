#include <stdio.h>
#include <stdlib.h>
#include "vectorsort.h"
#include "vector.h"
#include "ADTDefs.h"
#include "mu_test.h"

/*****************************/ /*TEST 1*/ /*Create Test*/
UNIT(Create_Normal_Inputs_Test)
    Vector *ptr = NULL;
    ptr = VectorCreate(10, 4);
    ASSERT_THAT( ptr != NULL);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 2*/
UNIT(Create_Zero_Both_Inputs_Test)
    Vector *ptr = NULL;
    ptr = VectorCreate(0, 0);
 	ASSERT_THAT( ptr == NULL);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 3*/
UNIT(Create_Zero_Initial_Size_Test)
    Vector *ptr = NULL;
    ptr = VectorCreate(0, 4);
 	ASSERT_THAT( ptr != NULL);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 4*/
UNIT(Create_Zero_IncrBlock_Test)
	Vector *ptr = NULL;
    ptr = VectorCreate(4, 0);
 	ASSERT_THAT( ptr != NULL);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 5*/
UNIT(Create_Huge_Initial_Allocation_Test)
	Vector *ptr = NULL;
    ptr = VectorCreate(123456789987456213, 5);
 	ASSERT_THAT( ptr == NULL);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 6*/ /*ADD Test*/
UNIT(Add_To_Null_Vector)
	Vector *ptr = NULL;
    ADTErr res;
	res = VectorAdd(ptr,5);
 	ASSERT_THAT(res == ERR_NOT_INITIALIZED);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 7*/
UNIT(Add_One_Element_Tets)
    ADTErr res;
    Vector *ptr = NULL;
    ptr = VectorCreate (3,3);
    res = VectorAdd(ptr, 5);
    ASSERT_THAT(res == ERR_OK);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 8*/
UNIT(Add_Few_Elements_Test)
    ADTErr res;
    int i;
    Vector *ptr = NULL;
    ptr = VectorCreate(10, 3);
    for (i=0; i<8; ++i)
    {
        res = VectorAdd(ptr, i+2);
    }
    ASSERT_THAT(res == ERR_OK);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 9*/
UNIT(Add_Elements_After_Realloc_OP_Test)
    ADTErr res;
    int i = 0;
    Vector *ptr = NULL;
    ptr = VectorCreate(5, 5);
    for (i=0; i < 25; ++i)
    {
        res = VectorAdd(ptr, i);
    }
    ASSERT_THAT(res == ERR_OK);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 10*/
UNIT(Add_Overflow_Test)
    Vector *ptr = NULL;
    int i = 0;
    ADTErr res;
    ptr = VectorCreate(10, 0);
    for (i=0; i < 13; ++i)
    {
        res = VectorAdd(ptr, i);
    }
    ASSERT_THAT(res == ERR_OVERFLOW);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 11*/
UNIT(Add_With_InitialSize_Zero_Test)
    ADTErr res;
    Vector *ptr = NULL;
    int i = 0;
    ptr = VectorCreate(0, 10);
    for (i=0; i < 15; ++i)
    {
        res = VectorAdd(ptr, i);
    }
    ASSERT_THAT(res == ERR_OK);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(ItemsNum_Null_Test)
    Vector *ptr = NULL;
    ADTErr res; 
    size_t noi=0;
    res = VectorItemsNum(NULL, &noi);
    ASSERT_THAT(res == ERR_NOT_INITIALIZED);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 13*/
UNIT(ItemsNum_Counting_Test)
    Vector *ptr = NULL;
    ADTErr res;
    size_t noi = 0;
    int i = 0;
    ptr = VectorCreate(10, 10);
    for (i=0; i < 7; ++i)
    {
        res = VectorAdd(ptr, i);
    }
    res = VectorItemsNum(ptr, &noi);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(noi == 7);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(Delete_Null_Test)
    Vector *ptr = NULL;
    ADTErr res;
    int noi = 0;
    res = VectorDelete(NULL, &noi);
    ASSERT_THAT(res == ERR_NOT_INITIALIZED);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(Delete_Underflow_Test)
    Vector *ptr = NULL;
    size_t noi = 5;
    int del;
    ADTErr res;
    ptr = VectorCreate(10, 10);
    res = VectorDelete(ptr, &del);
    ASSERT_THAT(res == ERR_UNDERFLOW);
    VectorItemsNum(ptr, &noi);
    ASSERT_THAT(noi == 0);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(Delete_One_Element_Test)
    Vector *ptr = NULL;
    ADTErr res;
    int noi =222;
    size_t nom =0;
    ptr = VectorCreate(10, 10);
    VectorAdd(ptr, 1);
    VectorAdd(ptr, 2);
    VectorAdd(ptr, 1);
    VectorAdd(ptr, 4);
    res = VectorDelete(ptr, &noi);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(noi == 4);   
    VectorItemsNum(ptr, &nom);
    ASSERT_THAT(nom == 3);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(Delete_Few_Elements_Test)
    Vector *ptr = NULL;
    ADTErr res;
    int noi1 = 0, noi2=0, noi3=0, noi4=0, i=0;
	size_t nom = 0;    
	ptr = VectorCreate(10, 10);
    for (i=0; i<8; ++i)
    {
        VectorAdd(ptr, i);
    }
    res = VectorDelete(ptr, &noi1);
    res = VectorDelete(ptr, &noi2);
    res = VectorDelete(ptr, &noi3);
    res = VectorDelete(ptr, &noi4);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(noi1 == 7);
    ASSERT_THAT(noi2 == 6);
    ASSERT_THAT(noi3 == 5);
    ASSERT_THAT(noi4 == 4);
    VectorItemsNum(ptr, &nom);
    ASSERT_THAT(nom == 4);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(Delete_With_Realloc_Test)
    Vector *ptr = NULL;
    ADTErr res;
    int noi1 = 0, i = 0, j = 20;
	size_t nom = 0;
    ptr = VectorCreate(10, 3);
    for (i=0; i < 20; ++i)
    {
        VectorAdd(ptr, i);
    }
    for (j=20; j > 15; --j)
    {
        res = VectorDelete(ptr, &noi1);
        ASSERT_THAT(res == ERR_OK);
        
        ASSERT_THAT(noi1 == j-1);
    }
    VectorItemsNum(ptr, &nom);
    ASSERT_THAT(nom == 15);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(Get_Null_Vec_Ptr_Test)
    Vector *ptr = NULL;
    ADTErr res;
    int noi = 0;
    res = VectorGet(NULL, 5, &noi);
    ASSERT_THAT(res == ERR_NOT_INITIALIZED);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(Get_Null_Var_Test)
    Vector *ptr = NULL;
    ADTErr res;
    ptr = VectorCreate(10, 3);
    res = VectorGet(ptr, 5, NULL);
    ASSERT_THAT(res == ERR_GENERAL);
    VectorDestroy(ptr);
END_UNIT

/*****************************/ /*TEST 12*/
UNIT(Get_Wrong_Index_Test)
    Vector *ptr = NULL;
    ADTErr res;
    int noi = 0;
    ptr = VectorCreate(10, 3);
    VectorAdd(ptr, 1);
    VectorAdd(ptr, 1);
    VectorAdd(ptr, 1);

    res = VectorGet(ptr, 4,&noi);
    ASSERT_THAT(res == ERR_WRONG_INDEX);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(Get_Prop_Index_Test)
    Vector *ptr = NULL;
    ADTErr res;
    int noi = 0;
    ptr = VectorCreate(10, 3);
    VectorAdd(ptr, 1);
    VectorAdd(ptr, 1);
    VectorAdd(ptr, 1);
    VectorAdd(ptr, 5);
    VectorAdd(ptr, 1);
    VectorAdd(ptr, 6);
    res = VectorGet(ptr, 3, &noi);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(noi == 5);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(Set_Null_Vec_Test)
    Vector *ptr = NULL;
    ADTErr res;
    int noi = 0;
    res = VectorSet(NULL, 5, noi);
    ASSERT_THAT(res == ERR_NOT_INITIALIZED);
    VectorDestroy(ptr);
END_UNIT

/*****************************/ /*TEST 12*/
UNIT(Set_Wrong_Index_Test)
    Vector *ptr = NULL;
    ADTErr res;
    int noi = 0;
    ptr = VectorCreate(10, 3);
    VectorAdd(ptr, 1);
    VectorAdd(ptr, 1);
    VectorAdd(ptr, 1);
    res = VectorSet(ptr, 4, noi);
    ASSERT_THAT(res == ERR_WRONG_INDEX);
    VectorDestroy(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(Set_Prop_Index_Test)
    Vector *ptr = NULL;
    ADTErr res;
    int noi = 0, getres=1;
    ptr = VectorCreate(10, 3);
    VectorAdd(ptr, 1);
    VectorAdd(ptr, 1);
    VectorAdd(ptr, 1);
    VectorAdd(ptr, 5);
    VectorAdd(ptr, 1);
    VectorAdd(ptr, 6);
    res = VectorSet(ptr, 3, noi);
    ASSERT_THAT(res == ERR_OK);
    VectorGet(ptr, 3, &getres);
    ASSERT_THAT(getres == 0);
    VectorDestroy(ptr);
END_UNIT

/*****************************/ /*TEST 12*/
UNIT(Massive_API_Vector_Use_Test)
    Vector *ptr = NULL;
    ADTErr addRes, setRes, itemsNumRes, getRes, delRes;
    int i=0, j=299, get, delData = 0;
    size_t noi ,index = 0;
    ptr = VectorCreate(50, 20);
    
    /*for add,set,get,itemsnum loop*/
    for (i=0; i < 300; ++i)
    {
        addRes = VectorAdd(ptr,i+1);
        ASSERT_THAT (addRes == ERR_OK);
        setRes = VectorSet(ptr,index,i+2);
        ASSERT_THAT(setRes == ERR_OK);
        itemsNumRes = VectorItemsNum(ptr, &noi);
        ASSERT_THAT(itemsNumRes == ERR_OK);
        ASSERT_THAT(noi == i+1);
        getRes = VectorGet(ptr, index, &get);
        ASSERT_THAT(getRes == ERR_OK);
        ASSERT_THAT(get == i+2);
    }
    
    /*for delete loop*/
    for (j=0; j>1; --j)
    {
        delRes = VectorDelete(ptr, &delData);
        ASSERT_THAT(delRes == ERR_OK);
        ASSERT_THAT (delData == j+2);
    }
    
    VectorDestroy(ptr);
END_UNIT
/******************************************************************************/


UNIT(Vector_Insertion_Sort_Test)
    Vector *ptr = NULL;
    int i;
    int item;
    ADTErr res;
    ptr = VectorCreate(3100, 3);
    for (i=0; i < 3000; ++i)
    {
        res = VectorAdd(ptr,3000-i);
        ASSERT_THAT (res == ERR_OK);
    }
	ASSERT_THAT(InsertionSort(ptr) == ERR_OK);
	for (i=0; i < 3000; ++i)
    {
        ASSERT_THAT(VectorGet(ptr,(size_t)i, &item) == ERR_OK);
        ASSERT_THAT(item == 1+i);
        ASSERT_THAT(res == ERR_OK);
    }
	
    VectorDestroy(ptr);
END_UNIT





/******************************************************************************/
/*Main function Macro*/
TEST_SUITE(Vector test)
	TEST(Create_Normal_Inputs_Test)
	TEST(Create_Zero_Both_Inputs_Test)
	TEST(Create_Zero_Initial_Size_Test)
	TEST(Create_Zero_IncrBlock_Test)
	TEST(Create_Huge_Initial_Allocation_Test)
	TEST(Add_To_Null_Vector)
    TEST(Add_One_Element_Tets)
    TEST(Add_Few_Elements_Test)
    TEST(Add_Elements_After_Realloc_OP_Test)
    TEST(Add_Overflow_Test)
    TEST(Add_With_InitialSize_Zero_Test)
    TEST(ItemsNum_Null_Test)
    TEST(ItemsNum_Counting_Test)
    TEST(Delete_Null_Test)
    TEST(Delete_Underflow_Test)
    TEST(Delete_One_Element_Test)
    TEST(Delete_Few_Elements_Test)
    TEST(Delete_With_Realloc_Test)
    TEST(Get_Null_Vec_Ptr_Test)
    TEST(Get_Null_Var_Test)
    TEST(Get_Wrong_Index_Test)
    TEST(Get_Prop_Index_Test)
    TEST(Set_Null_Vec_Test)
    TEST(Set_Wrong_Index_Test)
    TEST(Set_Prop_Index_Test)
    TEST(Massive_API_Vector_Use_Test)
    TEST(Vector_Insertion_Sort_Test)
END_SUITE
