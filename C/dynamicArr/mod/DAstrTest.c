#include <stdio.h>
#include "DAstr.h"
#include <stdlib.h>

/*color for printf function*/
#define RED "\x1B[31m"
#define RESET "\x1B[0m"

void PrintTestRes(int testResult);
void InsertDA_One_Element ();
void InsertDA_Few_Elements ();
void InsertDA_With_Incr_Zero ();
void InsertDA_With_Incr_Block ();
void InsertDA_After_Create_With_Size_ZERO ();
void DeleteDA_One_Element ();
void DeleteDA_Few_Elements ();
void DeleteDA_Empty_Array ();
void DeleteDA_Full_Array ();
void DeleteDA_AND_InsertDA ();

int main ()
{
    InsertDA_One_Element();
    InsertDA_Few_Elements();
    InsertDA_With_Incr_Zero();
    InsertDA_With_Incr_Block();
	InsertDA_After_Create_With_Size_ZERO ();
    DeleteDA_One_Element();
    DeleteDA_Few_Elements();
    DeleteDA_Empty_Array();
    DeleteDA_Full_Array();
    DeleteDA_AND_InsertDA();
    return 0;
}

void PrintTestRes(int testResult)
{
    if (testResult != 0)
    {
        printf(RED "FAIL\n");
        return;
    }
    printf(RESET "PASS\n");
    return;
}
void InsertDA_One_Element()
{
    size_t size = 5;
    size_t NOE = 0;
    size_t newsize = 5;
    int data = 1;
    size_t incr = 5;
    int rmdata = 0;
    int *DAptr = CreateDA(size);
    int res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    printf("InsertDA_One_Element___");
    PrintTestRes(res);
    DestroyDA(DAptr);
    return;
}
void InsertDA_Few_Elements()
{
    size_t size = 5;
    size_t NOE = 0;
    size_t newsize = 5;
    int data = 1;
    size_t incr = 5;
    int rmdata = 0;
    int *DAptr = CreateDA(size);
    int res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    printf("InsertDA_Few_Elements___");
    PrintTestRes(res);
    DestroyDA(DAptr);
    return;
}
void InsertDA_With_Incr_Zero()
{
    size_t size = 5;
    size_t NOE = 0;
    size_t newsize = 5;
    int data = 1;
    size_t incr = 0;
    int rmdata = 0;
    int *DAptr = CreateDA(size);
    int res1 = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    int res2 = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    int res3 = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    int res4 = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    int res5 = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    int res6 = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    printf("InsertDA_With_Incr_Zero___");
    PrintTestRes(res1+res2+res3+res4+res5+!res6);
    DestroyDA(DAptr);
    return;
}
void InsertDA_With_Incr_Block()
{
    size_t size = 5;
    size_t NOE = 0;
    size_t newsize = 5;
    int data = 1;
    size_t incr = 5;
    int rmdata = 0;
    int *DAptr = CreateDA(size);
    int res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);

    printf("InsertDA_With_Incr_Block___");
    PrintTestRes(res);
    DestroyDA(DAptr);
    return;
}
void InsertDA_After_Create_With_Size_ZERO ()
{
   	size_t size = 0;
    size_t NOE = 0;
    int data = 99;
    size_t incr = 5;
	int res1; int res2;
    int *DAptr = CreateDA(size);
    res1 = InsertDA(&DAptr, data, &NOE, &size, incr);
	res2 = InsertDA(&DAptr, data, &NOE, &size, incr);

    printf("InsertDA_After_Create_With_Size_ZERO___");
    PrintTestRes(res1+res2);
    DestroyDA(DAptr);
    return;
}

void DeleteDA_One_Element()
{
    size_t size = 5;
    size_t NOE = 0;
    size_t newsize = 5;
    int data = 1;
    size_t incr = 5;
    int rmdata = 0;
    int *DAptr = CreateDA(size);
    int res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = DeleteDA(DAptr, &rmdata, &NOE);
    printf("DeleteDA_One_Element___");
    PrintTestRes(res);
    DestroyDA(DAptr);
    return;
}
void DeleteDA_Few_Elements()
{
    size_t size = 5;
    size_t NOE = 0;
    size_t newsize = 5;
    int data = 1;
    size_t incr = 5;
    int rmdata = 0;
    int *DAptr = CreateDA(size);
    int res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    int res1 = DeleteDA(DAptr, &rmdata, &NOE);
    int res2 = DeleteDA(DAptr, &rmdata, &NOE);
    int res3 = DeleteDA(DAptr, &rmdata, &NOE);
    printf("DeleteDA_Few_Elements___");
    PrintTestRes(res1+res2+res3);
    DestroyDA(DAptr);
    return;
}
void DeleteDA_Empty_Array()
{
    size_t size = 5;
    size_t NOE = 0;
    size_t newsize = 5;
    int data = 1;
    size_t incr = 5;
    int rmdata = 0;
    int *DAptr = CreateDA(size);
    int res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    int res1 = DeleteDA(DAptr, &rmdata, &NOE);
    int res2 = DeleteDA(DAptr, &rmdata, &NOE);
    int res3 = DeleteDA(DAptr, &rmdata, &NOE);
    printf("DeleteDA_Empty_Array___");
    PrintTestRes(res1 + !res2 + !res3);
    DestroyDA(DAptr);
    return;
}

void DeleteDA_Full_Array()
{
    size_t size = 5;
    size_t NOE = 0;
    size_t newsize = 5;
    int data = -33;
    size_t incr = 0;
    int rmdata = 0;
    int *DAptr = CreateDA(size);
    int res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    int res1 = DeleteDA(DAptr, &rmdata, &NOE);
    int res2 = DeleteDA(DAptr, &rmdata, &NOE);
    int res3 = DeleteDA(DAptr, &rmdata, &NOE);
    int res4 = DeleteDA(DAptr, &rmdata, &NOE);
    int res5 = DeleteDA(DAptr, &rmdata, &NOE);
    printf("DeleteDA_Full_Array___");
    PrintTestRes(res1 + res2 + res3+ res4+ res5);
    DestroyDA(DAptr);
    return;
}
void DeleteDA_AND_InsertDA()
{
    size_t size = 5;
    size_t NOE = 0;
    size_t newsize = 5;
    int data = -33;
    size_t incr = 5;
    int rmdata = 0;
    int *DAptr = CreateDA(size);
    int res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    int res1 = DeleteDA(DAptr, &rmdata, &NOE);
    int res2 = DeleteDA(DAptr, &rmdata, &NOE);
    int res3 = DeleteDA(DAptr, &rmdata, &NOE);
    int res4 = DeleteDA(DAptr, &rmdata, &NOE);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    res = InsertDA(&DAptr, data, &NOE, &newsize, incr);
    printf("DeleteDA_AND_InsertDA___");
    PrintTestRes(res+res1+res2+res3+res4);
    DestroyDA(DAptr);
    return;
}
