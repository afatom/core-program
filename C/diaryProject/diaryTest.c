#include <stdio.h>
#include <stdlib.h>
#include "diary.h"
#include "ADTErr.h"
#include "mu_test.h"

/*****************************/ /*TEST 1*/ /*Create Test*/
UNIT(Create_Normal_Inputs_Test)
    ADPtr *ptr = NULL;
    ptr = CreateAD(10, 4);
    ASSERT_THAT( ptr != NULL);
    DestroyAD(ptr);
END_UNIT
/*****************************/ /*TEST 2*/
UNIT(Create_Zero_Both_Inputs_Test)
    ADPtr *ptr = NULL;
    ptr = CreateAD(0, 0);
 	ASSERT_THAT( ptr == NULL);
    DestroyAD(ptr);
END_UNIT
/*****************************/ /*TEST 3*/
UNIT(Create_Zero_Initial_Size_Test)
    ADPtr *ptr = NULL;
    ptr = CreateAD(0, 4);
 	ASSERT_THAT( ptr != NULL);
    DestroyAD(ptr);
END_UNIT
/*****************************/ /*TEST 4*/
UNIT(Create_Zero_IncrBlock_Test)
	ADPtr *ptr = NULL;
    ptr = CreateAD(4, 0);
 	ASSERT_THAT( ptr != NULL);
    DestroyAD(ptr);
END_UNIT
/*****************************/ /*TEST 5*/
UNIT(Create_Huge_Initial_Allocation_Test)
	ADPtr *ptr = NULL;
    ptr = CreateAD(123456789987456213, 5);
 	ASSERT_THAT( ptr == NULL);
    DestroyAD(ptr);
END_UNIT
/*****************************/ /*TEST 6*/ /*Insert Test*/
UNIT(Insert_To_Null_ADPtr)
	ADPtr *ptr = NULL;
    ADTErr res;
	res = InsertAD(ptr);
 	ASSERT_THAT(res == ERR_POINTER_NOT_INTIALIZED);
    DestroyAD(ptr);
END_UNIT
/*****************************/ /*TEST 7*/
UNIT(Insert_One_Meeting_Tets)
    ADTErr res;
    ADPtr *ptr = NULL;
    ptr = CreateAD (3,3);
    res = CreateMeetingAD(10.00, 11.00, 356, ptr);
    res = InsertAD(ptr);
    ASSERT_THAT(res == ERR_OK);
    DestroyAD(ptr);
END_UNIT
/*****************************/ /*TEST 8*/
UNIT(Insert_Few_Meetings_Test)
    ADTErr res;
    int i;
    ADPtr *ptr = NULL;
    ptr = CreateAD(10, 3);
    for (i=0; i<8; ++i)
    {
        res = CreateMeetingAD((float)(10.00+i),(float)(11.00+i),123+i, ptr);
        ASSERT_THAT(res == ERR_OK);
        res = InsertAD(ptr);
        ASSERT_THAT(res == ERR_OK);
    }
    ASSERT_THAT(res == ERR_OK);
    DestroyAD(ptr);
END_UNIT
/*****************************/ /*TEST 9*/
UNIT(Insert_Meetings_After_Realloc_OP_Test)
    ADTErr res;
    int i = 0;
    ADPtr *ptr = NULL;
    ptr = CreateAD(5, 5);
    for (i=0; i < 25; ++i)
    {
        res = CreateMeetingAD(10 + (float)(0.12*i), 11 + (float)(0.12*i), 123 + i, ptr);
        ASSERT_THAT(res == ERR_OK);
        res = InsertAD(ptr);
        ASSERT_THAT(res == ERR_OK);

    }
    ASSERT_THAT(res == ERR_OK);
    DestroyAD(ptr);
END_UNIT
/*****************************/ /*TEST 10*/
UNIT(Insert_Overflow_Test)
    ADPtr *ptr = NULL;
    int i = 0;
    ADTErr res;
    ptr = CreateAD(10, 0);
    for (i=0; i < 13; ++i)
    {
        res = CreateMeetingAD(10 + (float)(0.33*i), 11 + (float)(0.33*i), 123 + i, ptr);
        ASSERT_THAT(res == ERR_OK);
        res = InsertAD(ptr);
    }
    ASSERT_THAT(res == ERR_MEETINGS_ARRAY_OVERFLOW);
    DestroyAD(ptr);
END_UNIT
/*****************************/ /*TEST 11*/
UNIT(Insert_With_InitialSize_Zero_Test)
    ADTErr res;
    ADPtr *ptr = NULL;
    int i = 0;
    ptr = CreateAD(0, 10);
    for (i=0; i < 15; ++i)
    {
        res = CreateMeetingAD(10 + (float)(0.22*i), 11 + (float)(0.22*i), 123 + i, ptr);
        ASSERT_THAT(res == ERR_OK);
        res = InsertAD(ptr);
        ASSERT_THAT(res == ERR_OK);
    }
    ASSERT_THAT(res == ERR_OK);
    DestroyAD(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(ADMeetingsNum_Null_Test)
    ADPtr *ptr = NULL;
    ADTErr res; 
    size_t noi=0;
    res = ADMeetingsNum(NULL, &noi);
    ASSERT_THAT(res == ERR_POINTER_NOT_INTIALIZED);
    DestroyAD(ptr);
END_UNIT
/*****************************/ /*TEST 13*/
UNIT(ADMeetingsNum_Counting_Test)
    ADPtr *ptr = NULL;
    ADTErr res;
    size_t noi;
    size_t i;
    ptr = CreateAD(10, 10);
    for (i=0; i < 7; ++i)
    {
        res = CreateMeetingAD(10 + (float)(1*i)+(float)(0.1), 11 + (float)(1*i), 123 + (int)(i), ptr);
        ASSERT_THAT(res == ERR_OK);
        res = InsertAD(ptr);
        ASSERT_THAT(res == ERR_OK);
        res = ADMeetingsNum(ptr, &noi);
        ASSERT_THAT(res == ERR_OK);
        ASSERT_THAT(noi = i+1);
    }
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(noi == 7);
    DestroyAD(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(RemoveAD_Null_Test)
    ADPtr *ptr = NULL;
    ADTErr res;
    int noi = 0;
    res = RemoveAD(NULL, 10.00);
    ASSERT_THAT(res == ERR_POINTER_NOT_INTIALIZED);
    DestroyAD(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(RemoveAD_Underflow_Test)
    ADPtr *ptr = NULL;
    size_t noi = 5;
    ADTErr res;
    ptr = CreateAD(10, 10);
    res = RemoveAD(ptr, 10.00);
    ASSERT_THAT(res == ERR_MEETINGS_ARRAY_UNDERFLOW);
    ADMeetingsNum(ptr, &noi);
    ASSERT_THAT(noi == 0);
    DestroyAD(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(RemoveAD_One_Meeting_Test)
    ADPtr *ptr = NULL;
    ADTErr res;
    int noi =222;
    size_t nom =0;
    ptr = CreateAD(10, 10);
    res = CreateMeetingAD((float)10.30, (float)11.50, 523, ptr);
    InsertAD(ptr);
    res = RemoveAD(ptr, (float)10.30);
    ASSERT_THAT(res == ERR_OK);
    ADMeetingsNum(ptr, &nom);
    ASSERT_THAT(nom == 0);   
    DestroyAD(ptr);
END_UNIT
/*****************************/ /*TEST 12*/
UNIT(RemoveAD_Few_Meetings_Test)
    ADPtr *ptr = NULL;
    ADTErr res;
    int noi1 = 0, noi2=0, noi3=0, noi4=0, i=0;
	size_t nom = 0;    
    ptr = CreateAD(10, 10);
    /*1*/
    res = CreateMeetingAD((float)(10.30) ,(float)(11.00), 523, ptr);
    ASSERT_THAT(res == ERR_OK);
    res = InsertAD(ptr);
    ASSERT_THAT(res == ERR_OK);
    res = ADMeetingsNum(ptr, &nom);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(nom == 1);
    /*2*/
    res = CreateMeetingAD((float)21.30, (float)22.00, 523, ptr);
    ASSERT_THAT(res == ERR_OK);
    res = InsertAD(ptr);
    ASSERT_THAT(res == ERR_OK);
    res = ADMeetingsNum(ptr, &nom);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(nom == 2);
    /*3*/
    res = CreateMeetingAD((float)14.40, (float)16.00, 523, ptr);
    ASSERT_THAT(res == ERR_OK);
    res = InsertAD(ptr);
    ASSERT_THAT(res == ERR_OK);
    res = ADMeetingsNum(ptr, &nom);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(nom == 3);
    /*4*/
    res = CreateMeetingAD((float)19.30, (float)20.00, 523, ptr);
    ASSERT_THAT(res == ERR_OK);
    res = InsertAD(ptr);
    ASSERT_THAT(res == ERR_OK);
    res = ADMeetingsNum(ptr, &nom);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(nom == 4);
    /*5*/
    res = CreateMeetingAD((float)17.30, (float)18.00, 523, ptr);
    ASSERT_THAT(res == ERR_OK);
    res = InsertAD(ptr);
    ASSERT_THAT(res == ERR_OK);
    res = ADMeetingsNum(ptr, &nom);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(nom == 5);

    /*remove*/
    res = RemoveAD(ptr,(float)19.30);
    ASSERT_THAT(res == ERR_OK);
    res = ADMeetingsNum(ptr, &nom);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(nom == 4);

    res = RemoveAD(ptr, (float)21.30);
    ASSERT_THAT(res == ERR_OK);
    res = ADMeetingsNum(ptr, &nom);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(nom == 3);

    res = RemoveAD(ptr, (float)17.30);
    ASSERT_THAT(res == ERR_OK);
    res = ADMeetingsNum(ptr, &nom);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(nom == 2);

    res = RemoveAD(ptr,(float) 14.40);
    ASSERT_THAT(res == ERR_OK);
    res = ADMeetingsNum(ptr, &nom);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(nom == 1);

    res = RemoveAD(ptr,(float) 10.30);
    ASSERT_THAT(res == ERR_OK);
    res = ADMeetingsNum(ptr, &nom);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(nom == 0);
    DestroyAD(ptr);
END_UNIT
/*****************************/ /*TEST 12*/

UNIT(Massive_API_ADPtr_Use_Test)
    ADPtr *ptr = NULL;
    ADTErr res;
    size_t noi;
    int i,j;
    size_t index = 0;
    ptr = CreateAD(50, 20);
    
    /*for Insert,set,get,ADMeetingsNum loop*/
    for (i=0; i < 40; ++i)
    {
        res = CreateMeetingAD((float)(01.00+(0.51*i)),(float)(01.5+0.5*i), 1+i, ptr);
        ASSERT_THAT(res == ERR_OK);
        res = InsertAD(ptr);
        ASSERT_THAT(res == ERR_OK);
        res = ADMeetingsNum(ptr, &noi);
        ASSERT_THAT(res == ERR_OK);
        ASSERT_THAT(noi == i+1);
    }
    /*for RemoveAD loop*/
    
    for (j=0; j<40; ++j)
    {
        res = RemoveAD(ptr, (float)(01.00+(0.51)*j));
        ASSERT_THAT(res == ERR_OK);
        res = ADMeetingsNum(ptr, &noi);
        ASSERT_THAT(res == ERR_OK);
        ASSERT_THAT(noi == 39-j);
    }
    DestroyAD(ptr);
END_UNIT

/*Main function Macro*/
TEST_SUITE(Diary Project test)
	TEST(Create_Normal_Inputs_Test)
	TEST(Create_Zero_Both_Inputs_Test)
	TEST(Create_Zero_Initial_Size_Test)
	TEST(Create_Zero_IncrBlock_Test)
	TEST(Create_Huge_Initial_Allocation_Test)
	TEST(Insert_To_Null_ADPtr)
    TEST(Insert_One_Meeting_Tets)
    TEST(Insert_Few_Meetings_Test)
    TEST(Insert_Meetings_After_Realloc_OP_Test)
    TEST(Insert_Overflow_Test)
    TEST(Insert_With_InitialSize_Zero_Test)
    TEST(ADMeetingsNum_Null_Test)
    TEST(ADMeetingsNum_Counting_Test)
    TEST(RemoveAD_Null_Test)
    TEST(RemoveAD_Underflow_Test)
    TEST(RemoveAD_One_Meeting_Test)
    TEST(RemoveAD_Few_Meetings_Test)
    TEST(Massive_API_ADPtr_Use_Test)
END_SUITE
