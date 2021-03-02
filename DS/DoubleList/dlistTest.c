#include <stdio.h>
#include <stdlib.h>
#include "dlist.h"
#include "ADTDefs.h"
#include "mu_test.h"

/*****************************/ /*TEST 1*/ /*Create Test*/
UNIT(Create_Test)
    List *list = ListCreate();
    ASSERT_THAT(list != NULL);
    ListDestroy(list);
END_UNIT

UNIT(Push_Head_Null_Test)
    List *list = NULL;
    ADTErr res;
    res = ListPushHead(list, 1);
    ASSERT_THAT(res == ERR_NOT_INITIALIZED);
END_UNIT

UNIT(Push_Tail_Null_Test)
    List *list = NULL;
    ADTErr res;
    res = ListPushTail(list, 1);
    ASSERT_THAT(res == ERR_NOT_INITIALIZED);
END_UNIT

UNIT(List_Count_Zero_Items_Test)
    size_t cnt;
    List *list = ListCreate();
    cnt = ListCountItems(list);
    ASSERT_THAT(cnt == 0);
    ListDestroy(list);
END_UNIT

UNIT(Push_Head_One_Test)
    size_t cnt;
    List *list = ListCreate();
    ADTErr res;
    res = ListPushHead(list, 1);
    ASSERT_THAT(res == ERR_OK);
    cnt = ListCountItems(list);
    ASSERT_THAT(cnt == 1);
    ListDestroy(list);
END_UNIT

UNIT(List_Count_Few_Items_Test)
    size_t cnt;
    List *list = ListCreate();
    ADTErr res;
    res = ListPushHead(list, 1);
    ASSERT_THAT(res == ERR_OK);
    cnt = ListCountItems(list);
    ASSERT_THAT(cnt == 1);
    res = ListPushHead(list, 2);
    ASSERT_THAT(res == ERR_OK);
    cnt = ListCountItems(list);
    ASSERT_THAT(cnt == 2);
    res = ListPushHead(list, 3);
    ASSERT_THAT(res == ERR_OK);
    cnt = ListCountItems(list);
    ASSERT_THAT(cnt == 3);
    res = ListPushHead(list, 4);
    ASSERT_THAT(res == ERR_OK);
    cnt = ListCountItems(list);
    ASSERT_THAT(cnt == 4);
    ListDestroy(list);
END_UNIT

UNIT(Push_Head_Few_Test)
    size_t cnt;
    List *list = ListCreate();
    ADTErr res;
    res = ListPushHead(list, 1);
    ASSERT_THAT(res == ERR_OK);
    res = ListPushHead(list, 22);
    ASSERT_THAT(res == ERR_OK);
    res = ListPushHead(list, 33);
    ASSERT_THAT(res == ERR_OK);
    res = ListPushHead(list, 44);
    ASSERT_THAT(res == ERR_OK);
    cnt = ListCountItems(list);
    ASSERT_THAT(cnt == 4);
    ListDestroy(list);
END_UNIT

UNIT(Push_Head_Many_Test)
    size_t cnt;
    int i =0;
    List *list = ListCreate();
    ADTErr res;
    for (; i < 25; ++i)
    {
        res = ListPushHead(list, 1);
        ASSERT_THAT(res == ERR_OK);
    }
    cnt = ListCountItems(list);
    ASSERT_THAT(cnt == 25);
    ListDestroy(list);
END_UNIT

UNIT(Push_Tail_One_Test)
    size_t cnt;
    List *list = ListCreate();
    ADTErr res;
    res = ListPushTail(list, 1);
    ASSERT_THAT(res == ERR_OK);
    cnt = ListCountItems(list);
    ASSERT_THAT(cnt == 1);
    ListDestroy(list);
END_UNIT

UNIT(Push_Tail_Few_Test)
    size_t cnt;
    List *list = ListCreate();
    ADTErr res;
    res = ListPushTail(list, 1);
    ASSERT_THAT(res == ERR_OK);
    res = ListPushTail(list, 22);
    ASSERT_THAT(res == ERR_OK);
    res = ListPushTail(list, 33);
    ASSERT_THAT(res == ERR_OK);
    res = ListPushTail(list, 44);
    ASSERT_THAT(res == ERR_OK);
    cnt = ListCountItems(list);
    ASSERT_THAT(cnt == 4);
    ListDestroy(list);
END_UNIT

UNIT(Push_Tail_Many_Test)
    size_t cnt;
    int i = 0;
    List *list = ListCreate();
    ADTErr res;
    for (; i < 25; ++i)
    {
        res = ListPushTail(list, 1);
        ASSERT_THAT(res == ERR_OK);
    }
    cnt = ListCountItems(list);
    ASSERT_THAT(cnt == 25);
    ListDestroy(list);
END_UNIT

UNIT(Pop_Head_One_Test)
    size_t cnt;
    int i = 0;
    int data;
    List *list = ListCreate();
    ADTErr res;
    for (; i < 6; ++i)
    {
        res = ListPushHead(list, i);
        ASSERT_THAT(res == ERR_OK);
    }
    cnt = ListCountItems(list);
    ASSERT_THAT(cnt == 6);
    res = ListPopHead(list, &data);
    ASSERT_THAT(res == ERR_OK);
    cnt = ListCountItems(list);
    ASSERT_THAT(cnt == 5);
    ASSERT_THAT(data == 5);
    ListDestroy(list);
END_UNIT

UNIT(Pop_Head_Few_Test)
    size_t cnt;
    int i = 0, j =0;
    int data;
    List *list = ListCreate();
    ADTErr res;
    for (; i < 10; ++i)
    {
        res = ListPushHead(list, i);
        ASSERT_THAT(res == ERR_OK);
    }
    cnt = ListCountItems(list);
    ASSERT_THAT(cnt == 10);
    res = ListPopHead(list, &data);
    ASSERT_THAT(res == ERR_OK);
    cnt = ListCountItems(list);
    ASSERT_THAT(cnt == 9);
    ASSERT_THAT(data == 9);
    for(; j < 9; ++j)
    {
        res = ListPopHead(list, &data);
        ASSERT_THAT(res == ERR_OK);
        ASSERT_THAT(data == 8-j);
        cnt = ListCountItems(list);
        ASSERT_THAT(res == ERR_OK);
        ASSERT_THAT(cnt == 8-j);
    }
    ListDestroy(list);
END_UNIT

UNIT(Pop_Head_Many_Test)
    size_t cnt;
    int i = 0, j = 0;
    int data;
    List *list = ListCreate();
    ADTErr res;
    for (; i < 100; ++i)
    {
        res = ListPushHead(list, i);
        ASSERT_THAT(res == ERR_OK);
    }
    cnt = ListCountItems(list);
    ASSERT_THAT(cnt == 100);
    res = ListPopHead(list, &data);
    ASSERT_THAT(res == ERR_OK);
    cnt = ListCountItems(list);
    ASSERT_THAT(cnt == 99);
    ASSERT_THAT(data == 99);
    for (; j < 98; ++j)
    {
        res = ListPopHead(list, &data);
        ASSERT_THAT(res == ERR_OK);
        ASSERT_THAT(data == 98 - j);
        cnt = ListCountItems(list);
        ASSERT_THAT(res == ERR_OK);
        ASSERT_THAT(cnt == 98 - j);
    }
    ListDestroy(list);
END_UNIT
/******************************************************************************/
UNIT(Pop_Tail_Empty_List_Test)
  size_t cnt;
  List *list = ListCreate();
  ADTErr res;
  int data;
  cnt = ListCountItems(list);
  ASSERT_THAT(cnt == 0);
  res = ListPopTail(list, &data);
  ASSERT_THAT(res == ERR_UNDERFLOW);
  ListDestroy(list);
END_UNIT
/******************************************************************************/
/******************************************************************************/
UNIT(Pop_Head_Empty_List_Test)
  size_t cnt;
  List *list = ListCreate();
  ADTErr res;
  int data;
  cnt = ListCountItems(list);
  ASSERT_THAT(cnt == 0);
  res = ListPopHead(list, &data);
  ASSERT_THAT(res == ERR_UNDERFLOW);
  ListDestroy(list);
END_UNIT
/******************************************************************************/

UNIT(Pop_Tail_One_Test)
  size_t cnt;
  int i = 0;
  int data;
  List *list = ListCreate();
  ADTErr res;
  for (; i < 6; ++i)
  {
      res = ListPushTail(list, i);
      ASSERT_THAT(res == ERR_OK);
  }
  cnt = ListCountItems(list);
  ASSERT_THAT(cnt == 6);
  res = ListPopTail(list, &data);
  ASSERT_THAT(res == ERR_OK);
  cnt = ListCountItems(list);
  ASSERT_THAT(cnt == 5);
  ASSERT_THAT(data == 5);
  ListDestroy(list);
END_UNIT

UNIT(Pop_Tail_Few_Test)
size_t cnt;
int i = 0, j = 0;
int data;
List *list = ListCreate();
ADTErr res;
for (; i < 10; ++i)
{
    res = ListPushTail(list, i);
    ASSERT_THAT(res == ERR_OK);
}
cnt = ListCountItems(list);
ASSERT_THAT(cnt == 10);
res = ListPopTail(list, &data);
ASSERT_THAT(res == ERR_OK);
cnt = ListCountItems(list);
ASSERT_THAT(cnt == 9);
ASSERT_THAT(data == 9);
for (; j < 9; ++j)
{
    res = ListPopTail(list, &data);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(data == 8 - j);
    cnt = ListCountItems(list);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(cnt == 8 - j);
}
ListDestroy(list);
END_UNIT

UNIT(Pop_Tail_Many_Test)
size_t cnt;
int i = 0, j = 0;
int data;
List *list = ListCreate();
ADTErr res;
for (; i < 100; ++i)
{
    res = ListPushTail(list, i);
    ASSERT_THAT(res == ERR_OK);
}
cnt = ListCountItems(list);
ASSERT_THAT(cnt == 100);
res = ListPopTail(list, &data);
ASSERT_THAT(res == ERR_OK);
cnt = ListCountItems(list);
ASSERT_THAT(cnt == 99);
ASSERT_THAT(data == 99);
for (; j < 98; ++j)
{
    res = ListPopTail(list, &data);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(data == 98 - j);
    cnt = ListCountItems(list);
    ASSERT_THAT(res == ERR_OK);
    ASSERT_THAT(cnt == 98 - j);
}
ListDestroy(list);
END_UNIT

UNIT(List_Is_Empty_Test)
    size_t cnt;
    int i = 0;
    int data;
    int isempty;
    List *list = ListCreate();
    ADTErr res;
    isempty = ListIsEmpty(list);
    ASSERT_THAT(isempty == 1);
    for (; i < 10; ++i)
    {
        res = ListPushTail(list, i);
        ASSERT_THAT(res == ERR_OK);
    }
    cnt = ListCountItems(list);
    ASSERT_THAT(cnt == 10);
    isempty = ListIsEmpty(list);
    ASSERT_THAT(isempty ==0);
    res = ListPopTail(list, &data);
    ASSERT_THAT(res == ERR_OK);
    cnt = ListCountItems(list);
    ASSERT_THAT(cnt == 9);
    ASSERT_THAT(data == 9);
    isempty = ListIsEmpty(list);
    ASSERT_THAT(isempty ==0);

END_UNIT

    /*Main function Macro*/
TEST_SUITE(Double Linked List test)
    TEST(Create_Test)
    TEST(Push_Head_Null_Test)
    TEST(Push_Tail_Null_Test)
    TEST(List_Count_Zero_Items_Test)
    TEST(Push_Head_One_Test)
    TEST(List_Count_Few_Items_Test)
    TEST(Push_Head_Few_Test)
    TEST(Push_Head_Many_Test)
    TEST(Push_Tail_One_Test)
    TEST(Push_Tail_Few_Test)
    TEST(Push_Tail_Many_Test)
    TEST(Pop_Head_One_Test)
    TEST(Pop_Head_Few_Test)
    TEST(Pop_Head_Many_Test)
    TEST(Pop_Tail_One_Test)
    TEST(Pop_Tail_Few_Test)
    TEST(Pop_Tail_Many_Test)
    TEST(Pop_Tail_Empty_List_Test)
    TEST(Pop_Head_Empty_List_Test)
    TEST(List_Is_Empty_Test)
END_SUITE
