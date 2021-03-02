#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "mu_test.h"
#include <string.h>
#include <time.h>

Person *CreatePerson(int id, const char *str, int age)
{
    Person *ptr = NULL;
    ptr = (Person *)malloc(sizeof(Person));
    if (NULL == ptr)
    {
        return NULL;
    }
    ptr->m_id = id;
    ptr->m_age = age;
    strcpy(ptr->m_name, str);
    ptr->m_next = NULL;
    return ptr;
}

UNIT(Time_Initializer)
srand((unsigned int)time(NULL));
END_UNIT
/*****************************/ /*TEST 1*/ /*Create Test*/
UNIT(Insert_One_Head_Test)
    Person *head = NULL;
    Person *p1 = CreatePerson(23850, "niko", 39);
    head = ListInsertHead(head, p1);
    ASSERT_THAT(head == p1);
    ASSERT_THAT(head->m_next == NULL);
    ASSERT_THAT(head->m_id == 23850);
    ASSERT_THAT(head->m_age == 39);
    free(p1);
END_UNIT
/*****************************/ /*TEST 2*/
UNIT(Insert_few_heads_test)
    Person *head = NULL;
    int strcmpr;
    Person *p2 = CreatePerson(2, "niko", 33);
    Person *p3 = CreatePerson(5, "rambo", 32);
    Person *p4 = CreatePerson(4, "zoro", 33);
    Person *p5 = CreatePerson(3, "foo", 33);
    head = ListInsertHead(head, p2);
    head = ListInsertHead(head, p3);
    head = ListInsertHead(head, p4);
    head = ListInsertHead(head, p5);
    ASSERT_THAT(head == p5);
    ASSERT_THAT(head->m_id == 3);
    ASSERT_THAT(head->m_age == 33);
    strcmpr = strcmp(head->m_name, "foo");
    ASSERT_THAT(strcmpr == 0);
    free(p2);
    free(p3);
    free(p4);
    free(p5);
END_UNIT
/*****************************/ /*TEST 3*/
UNIT(Insert_Null_head_test)
Person *head = NULL;
head = ListInsertHead(head, NULL);
ASSERT_THAT(head == NULL);

END_UNIT
/*****************************/ /*TEST 4*/
UNIT(Insert_Many_Heads)
int i;
Person *head = NULL;
Person **arr = NULL;
arr = (Person **)malloc(1024 * sizeof(Person*));
for(i = 0; i < 1024; ++i)
{
    arr[i] = CreatePerson(i, "A", i);
}
for (i = 1023; i >=0; --i)
{
    head = ListInsertHead(head, arr[i]);
}
ASSERT_THAT(head->m_age == 0);
ASSERT_THAT(head->m_id == 0);
for (i = 0; i < 1024; ++i)
{
    free(arr[i]);
}
free(arr);
END_UNIT
/*****************************/ /*TEST 5*/
/*****************************/ /*TEST 1*/ /*Create Test*/
UNIT(Insert_BYKey_One_Head_Test)
Person *head = NULL;
int strcmpr;
Person *p2 = CreatePerson(21234, "niko", 323);
head = ListInsertByKey(head, 21234, p2);

ASSERT_THAT(head == p2);
ASSERT_THAT(head->m_id == 21234);
ASSERT_THAT(head->m_age == 323);
strcmpr = strcmp(head->m_name, "niko");
ASSERT_THAT(strcmpr == 0);
free(p2);
END_UNIT
/*****************************/ /*TEST 2*/
UNIT(Insert_BYKey_few_heads_test)
Person *head = NULL;
Person *p1 = CreatePerson(21, "niko", 23);
Person *p2 = CreatePerson(23, "adam", 124);
Person *p3 = CreatePerson(29, "niasdfgvcko", 512);
Person *p4 = CreatePerson(1, "asdc", 32);
Person *p5 = CreatePerson(211, "niasdao", 69);
Person *p7 = CreatePerson(9, "mmo", 33);
Person *p8 = CreatePerson(699, "asdwko", 3);
Person *p6 = CreatePerson(458, "bngaso", 63);

head = ListInsertByKey(head, 23, p2);
head = ListInsertByKey(head, 29, p3);
head = ListInsertByKey(head, 1, p4);
head = ListInsertByKey(head, 211, p5);
head = ListInsertByKey(head, 458, p6);
head = ListInsertByKey(head, 9, p7);
head = ListInsertByKey(head, 699, p8);
head = ListInsertByKey(head, 21, p1);
/*PrintList(head);*/
ASSERT_THAT(head == p4);
free(p2);
free(p1);
free(p3);
free(p4);
free(p5);
free(p6);
END_UNIT
/*****************************/ /*TEST 3*/
UNIT(Insert_BYKey_Null_head_test)
Person *head = NULL;
head = ListInsertByKey(head, 0,NULL);
ASSERT_THAT(head == NULL);

END_UNIT
/*****************************/ /*TEST 4*/
UNIT(Insert_BYKey_Many_Heads)
int i;
Person *head = NULL;
Person **arr = NULL;


arr = (Person **)malloc(1024 * sizeof(Person *));
for (i = 0; i < 1024; ++i)
{
    arr[i] = CreatePerson(rand()%100, "A", i);
}
for (i = 1023; i >= 0; --i)
{
    head = ListInsertByKey(head, arr[i]->m_id,arr[i]);
}
/*PrintList(head);*/

for (i = 0; i < 1024; ++i)
{
    free(arr[i]);
}
free(arr);
END_UNIT
/*****************************/ /*TEST 5*/
UNIT(Insert_BYKeyRec_One_Head_Test)
Person *head = NULL;
int strcmpr;
Person *p2 = CreatePerson(21234, "niko", 323);
head = ListInsertByKeyRec(head, 21234, p2);

ASSERT_THAT(head == p2);
ASSERT_THAT(head->m_id == 21234);
ASSERT_THAT(head->m_age == 323);
strcmpr = strcmp(head->m_name, "niko");
ASSERT_THAT(strcmpr == 0);
free(p2);
END_UNIT
/*****************************/ /*TEST 2*/
UNIT(Inser_BYKeyRec_few_heads_test)
Person *head = NULL;
Person *p1 = CreatePerson(21, "niko", 23);
Person *p2 = CreatePerson(23, "adam", 124);
Person *p3 = CreatePerson(29, "niasdfgvcko", 512);
Person *p4 = CreatePerson(1, "asdc", 32);
Person *p5 = CreatePerson(211, "niasdao", 69);
Person *p7 = CreatePerson(9, "mmo", 33);
Person *p8 = CreatePerson(699, "asdwko", 3);
Person *p6 = CreatePerson(458, "bngaso", 63);

head = ListInsertByKeyRec(head, 23, p2);
head = ListInsertByKeyRec(head, 29, p3);
head = ListInsertByKeyRec(head, 1, p4);
head = ListInsertByKeyRec(head, 211, p5);
head = ListInsertByKeyRec(head, 458, p6);
head = ListInsertByKeyRec(head, 9, p7);
head = ListInsertByKeyRec(head, 699, p8);
head = ListInsertByKeyRec(head, 21, p1);
/*PrintList(head);*/
ASSERT_THAT(head == p4);
free(p2);
free(p1);
free(p3);
free(p4);
free(p5);
free(p6);
END_UNIT
/*****************************/ /*TEST 3*/
UNIT(Insert_BYKeyRec_Null_head_test)
Person *head = NULL;
head = ListInsertByKeyRec(head, 0,NULL);
ASSERT_THAT(head == NULL);
END_UNIT
/*****************************/ /*TEST 4*/
UNIT(Inser_BYKeyRec_Many_Heads)
int i;
Person *head = NULL;
Person **arr = NULL;


arr = (Person **)malloc(1024 * sizeof(Person *));
for (i = 0; i < 1024; ++i)
{
    arr[i] = CreatePerson(rand()%100, "A", i);
}
for (i = 1023; i >= 0; --i)
{
    head = ListInsertByKeyRec(head, arr[i]->m_id,arr[i]);
}
/*PrintList(head);*/

for (i = 0; i < 1024; ++i)
{
    free(arr[i]);
}
free(arr);
END_UNIT


UNIT(Remove_One_Head_Test)
Person *head = NULL;
Person* removed = NULL;
int strcmpr;
Person *p2 = CreatePerson(21234, "niko", 323);
head = ListInsertByKeyRec(head, 21234, p2);

ASSERT_THAT(head == p2);
ASSERT_THAT(head->m_id == 21234);
ASSERT_THAT(head->m_age == 323);
strcmpr = strcmp(head->m_name, "niko");
ASSERT_THAT(strcmpr == 0);
PrintList(head);
ASSERT_THAT();
ListRemoveHead(head, &removed);
PrintList(head);
free(removed);
END_UNIT
/*****************************/ /*TEST 2*/
UNIT(Remove_few_heads_test)

END_UNIT
/*****************************/ /*TEST 3*/
UNIT(Remove_Null_head_test)

END_UNIT
/*****************************/ /*TEST 4*/
UNIT(Remove_Many_Heads)

END_UNIT
/*****************************/ /*TEST 5*/
UNIT(RemoveBykey_One_Head_Test)

END_UNIT
/*****************************/ /*TEST 2*/
UNIT(RemoveBykey_few_heads_test)

END_UNIT
/*****************************/ /*TEST 3*/
UNIT(RemoveBykey_Null_head_test)

END_UNIT
/*****************************/ /*TEST 4*/
UNIT(RemoveByKey_Many_Heads)

END_UNIT
/*****************************/ /*TEST 5*/
UNIT(RemoveBykeyRec_One_Head_Test)

END_UNIT
/*****************************/ /*TEST 2*/
UNIT(RemoveBykeyRec_few_heads_test)

END_UNIT
/*****************************/ /*TEST 3*/
UNIT(RemoveBykeyRec_Null_head_test)

END_UNIT
/*****************************/ /*TEST 4*/
UNIT(RemoveByKeyRec_Many_Heads)
END_UNIT

UNIT(Massive_API_LinkedList_Use_Test)
END_UNIT

/************************************************************************/
/*Main function Macro*/
TEST_SUITE(Linked List Test)
    TEST(Time_Initializer)
    TEST(RemoveByKeyRec_Many_Heads)
    TEST(Insert_One_Head_Test)
    TEST(Insert_few_heads_test)
    TEST(Insert_Null_head_test)
    TEST(Insert_Many_Heads)
    TEST(Insert_BYKey_One_Head_Test)
    TEST(Insert_BYKey_few_heads_test)
    TEST(Insert_BYKey_Null_head_test)
    TEST(Insert_BYKey_Many_Heads)
    TEST(Insert_BYKeyRec_One_Head_Test)
    TEST(Inser_BYKeyRec_few_heads_test)
    TEST(Inser_BYKeyRec_Many_Heads)
    TEST(Insert_BYKeyRec_Null_head_test)
    TEST(Remove_One_Head_Test)
END_SUITE
