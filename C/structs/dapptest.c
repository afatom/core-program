#include "dapp.h"
#include <stdlib.h>
#include <stdio.h>

/*color for printf function*/
#define RED "\x1B[31m"
#define RESET "\x1B[0m"

void PrintTestRes(int testResult);
void InsertDA_One_Element ();
void InsertDA_With_Incr_Block_Zero ();
void InsertDA_With_Realloc ();
void InsertDA_After_Delete_Operation ();
void InsertDA_Few_Elements ();
void InsertDA_After_Create_With_Size_ZERO ();
void InsertDA_After_Create_With_Size_And_IncrBlock_ZERO();
void DeleteDA_One_Element();
void DeleteDA_Few_Elements();
void DeleteDA_Empty_Array();
void DeleteDA_Full_Array();
void DeleteDA_AND_InsertDA();
void DeleteDA_After_Create_With_Size_Zero ();
void DeleteDA_After_Reallocation ();

int main ()
{
    InsertDA_One_Element ();
    InsertDA_With_Incr_Block_Zero ();
    InsertDA_With_Realloc ();
    InsertDA_After_Delete_Operation ();
    InsertDA_Few_Elements ();
    InsertDA_After_Create_With_Size_ZERO ();
    InsertDA_After_Create_With_Size_And_IncrBlock_ZERO ();
    DeleteDA_One_Element ();
    DeleteDA_Few_Elements ();
    DeleteDA_Empty_Array ();
    DeleteDA_Full_Array ();
    DeleteDA_AND_InsertDA ();
    DeleteDA_After_Create_With_Size_Zero ();
    DeleteDA_After_Reallocation();

        return 0;
}
/**********************************************/
/*Test Segment Code*/
void PrintTestRes(int testResult)
{
    if (testResult != 0)
    {
        printf(RED "FAIL");
        return;
    }
    printf(RESET "PASS");
    return;
}

void InsertDA_One_Element()
{
    size_t size = 5;
    size_t IncrBlockSize = 5;
    int data = 789;
    int res;
    DA *DAPtr = CreateDA(size, IncrBlockSize);
    res = InsertDA(DAPtr, data);
    PrintTestRes(res);
    printf("_____________InsertDA_One_Element\n");
    DestroyDA (DAPtr);
    return;
}

void InsertDA_Few_Elements ()
{
    size_t size = 5;
    size_t IncrBlockSize = 5;
    int data = 789;
    int res;
    DA *DAPtr = CreateDA(size, IncrBlockSize);
    res = InsertDA(DAPtr, data);
    res = InsertDA(DAPtr, data);
    res = InsertDA(DAPtr, data);
    res = InsertDA(DAPtr, data);
    PrintTestRes(res);
    printf("_____________InsertDA_Few_Elements\n");
    DestroyDA(DAPtr);
    return;
}

void InsertDA_With_Incr_Block_Zero()
{
    size_t size = 5;
    size_t IncrBlockSize = 0;
    int data = 789;
    int res1; int res2; int res3;
    DA *DAPtr = CreateDA(size, IncrBlockSize);
    res1 = InsertDA(DAPtr, data);
    res2 = InsertDA(DAPtr, data);
    res3 = InsertDA(DAPtr, data);
    PrintTestRes(res1 + res2 + res3);
    printf("_____________InsertDA_With_Incr_Block_Zero\n");
    DestroyDA(DAPtr);
    return;
}

void InsertDA_After_Create_With_Size_And_IncrBlock_ZERO ()
{
    size_t size = 0;
    size_t IncrBlockSize = 0;
    int data = 789;
    int res1;
    int res2;
    int res3;
    DA *DAPtr = CreateDA(size, IncrBlockSize);
    res1 = InsertDA(DAPtr, data);
    /*
    res2 = InsertDA(DAPtr, data);
    res3 = InsertDA(DAPtr, data);
    */
    PrintTestRes(!res1 );
    printf("_____________InsertDA_After_Create_With_Size_And_IncrBlock_ZERO\n");
    DestroyDA(DAPtr);
    return;
}

void InsertDA_With_Realloc()
{
    size_t size = 3;
    size_t IncrBlockSize = 3;
    int data = 789;
    int res1;
    int res2;
    int res3;
    DA *DAPtr = CreateDA(size, IncrBlockSize);
    res1 = InsertDA(DAPtr, data);
    res2 = InsertDA(DAPtr, data);
    res3 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res2 = InsertDA(DAPtr, data);
    res3 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res2 = InsertDA(DAPtr, data);
    res3 = InsertDA(DAPtr, data);
    PrintTestRes(res1 + res2 + res3);
    printf("_____________InsertDA_With_Realloc\n");
    DestroyDA(DAPtr);
    return;
}

void InsertDA_After_Create_With_Size_ZERO ()
{
    size_t size = 0;
    size_t IncrBlockSize = 6;
    int data = 789;
    int res1;
    int res2;
    int res3;
    DA *DAPtr = CreateDA(size, IncrBlockSize);
    res1 = InsertDA(DAPtr, data);
    res2 = InsertDA(DAPtr, data);
    res3 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res2 = InsertDA(DAPtr, data);
    res3 = InsertDA(DAPtr, data);
    PrintTestRes(res1 + res2 + res3);
    printf("_____________InsertDA_After_Create_With_Size_ZERO\n");

    DestroyDA(DAPtr);
    return;
}

void InsertDA_After_Delete_Operation ()
{
    size_t size = 3;
    size_t IncrBlockSize = 3;
    int data = 789;
    int res1; int res;
    int res2;
    int res3;
    int rmdata1 = 0;
    int rmdata2 = 0;
    DA *DAPtr = CreateDA(size, IncrBlockSize);
    res1 = InsertDA(DAPtr, data);
    res2 = InsertDA(DAPtr, data);
    res3 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res2 = InsertDA(DAPtr, data);
    res = DeleteDA(DAPtr, &rmdata1);
    res = DeleteDA(DAPtr, &rmdata2);
    res = DeleteDA(DAPtr, &rmdata1);
    res3 = InsertDA(DAPtr, data);
    res = DeleteDA(DAPtr, &rmdata2);
    res = DeleteDA(DAPtr, &rmdata2);
    res3 = InsertDA(DAPtr, data);
    PrintTestRes(res1 + res2 + res3 + res);
    printf("_____________InsertDA_After_Delete_Operation\n");

    DestroyDA(DAPtr);
    return;
}
void DeleteDA_One_Element ()
{
    size_t size = 3;
    size_t IncrBlockSize = 3;
    int data = 789;
    int res1;
    int res2;
    int rmdata1 = 0;
    DA *DAPtr = CreateDA(size, IncrBlockSize);
    res1 = InsertDA(DAPtr, data);
    res2 = DeleteDA(DAPtr, &rmdata1);
    PrintTestRes(res1 + res2);
    printf("_____________DeleteDA_One_Element\n");

    DestroyDA(DAPtr);
    return;
}
void DeleteDA_Few_Elements ()
{
    size_t size = 3;
    size_t IncrBlockSize = 3;
    int data = 789;
    int res1;
    int res;
    int res2;
    int res3;
    int rmdata1 = 0;
    int rmdata2 = 0;
    DA *DAPtr = CreateDA(size, IncrBlockSize);
    res1 = InsertDA(DAPtr, data);
    res2 = InsertDA(DAPtr, data);
    res3 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res2 = InsertDA(DAPtr, data);
    res = DeleteDA(DAPtr, &rmdata1);
    res = DeleteDA(DAPtr, &rmdata2);
    res = DeleteDA(DAPtr, &rmdata1);
    res3 = InsertDA(DAPtr, data);
    res = DeleteDA(DAPtr, &rmdata2);
    res = DeleteDA(DAPtr, &rmdata2);
    res3 = InsertDA(DAPtr, data);
    PrintTestRes(res1 + res2 + res3 + res);
    printf("_____________DeleteDA_Few_Elements\n");

    DestroyDA(DAPtr);
    return;
}
void DeleteDA_Empty_Array ()
{
    size_t size = 3;
    size_t IncrBlockSize = 3;
    int res;
    int rmdata1 = 0;
    DA *DAPtr = CreateDA(size, IncrBlockSize);
    res = DeleteDA(DAPtr, &rmdata1);
    PrintTestRes(!res);
    printf("_____________DeleteDA_Empty_Array\n");

    DestroyDA(DAPtr);
    return;
}
void DeleteDA_Full_Array ()
{
    size_t size = 5;
    size_t IncrBlockSize = 3;
    int data = 789;
    int res1;
    int res2;
    int rmdata1 = 0;
    int rmdata2 = 0;
    DA *DAPtr = CreateDA(size, IncrBlockSize);
    res1 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res2 = DeleteDA(DAPtr, &rmdata1);
    res2 = DeleteDA(DAPtr, &rmdata2);
    res2 = DeleteDA(DAPtr, &rmdata1);
    res2 = DeleteDA(DAPtr, &rmdata2);
    res2 = DeleteDA(DAPtr, &rmdata1);
    PrintTestRes(res2);
    printf("_____________DeleteDA_Full_Array\n");

    DestroyDA(DAPtr);
    return;
}
void DeleteDA_AND_InsertDA ()
{
    size_t size = 5;
    size_t IncrBlockSize = 3;
    int data = 789;
    int res1;
    int res2;
    int rmdata1 = 0;
    int rmdata2 = 0;
    DA *DAPtr = CreateDA(size, IncrBlockSize);
    res1 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res2 = DeleteDA(DAPtr, &rmdata1);
    res2 = DeleteDA(DAPtr, &rmdata2);
    res2 = DeleteDA(DAPtr, &rmdata1);
    res1 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    PrintTestRes(res2 + res1);
    printf("_____________DeleteDA_AND_InsertDA\n");
 
    DestroyDA(DAPtr);
    return;
}
void DeleteDA_After_Create_With_Size_Zero ()
{
    size_t size = 0;
    size_t IncrBlockSize = 3;
    int data = 789;
    int res1;
    int res2;
    int rmdata1 = 0;
    int rmdata2 = 0;
    DA *DAPtr = CreateDA(size, IncrBlockSize);
    res1 = DeleteDA(DAPtr, &rmdata1);
    res2 = DeleteDA(DAPtr, &rmdata2);
    PrintTestRes(!res2 + !res1);
    printf("_____________DeleteDA_After_Create_With_Size_Zero\n");

    DestroyDA(DAPtr);
    return;
}
void DeleteDA_After_Reallocation ()
{
    size_t size = 5;
    size_t IncrBlockSize = 3;
    int data = 789;
    int res1;
    int res2;
    int rmdata1 = 0;
    DA *DAPtr = CreateDA(size, IncrBlockSize);
    res1 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);
    res1 = InsertDA(DAPtr, data);

    res2 = DeleteDA(DAPtr, &rmdata1);
    res2 = DeleteDA(DAPtr, &rmdata1);
    res2 = DeleteDA(DAPtr, &rmdata1);
    res2 = DeleteDA(DAPtr, &rmdata1);
    res2 = DeleteDA(DAPtr, &rmdata1);
    res2 = DeleteDA(DAPtr, &rmdata1);
    res2 = DeleteDA(DAPtr, &rmdata1);
    res2 = DeleteDA(DAPtr, &rmdata1);
    res2 = DeleteDA(DAPtr, &rmdata1);
    res2 = DeleteDA(DAPtr, &rmdata1);
    res2 = DeleteDA(DAPtr, &rmdata1);


    PrintTestRes(res2 + res1);
    printf("_____________DeleteDA_After_Reallocation\n");

    DestroyDA(DAPtr);
    return;
}