#include <stdio.h>
#include "gsort.h"
#include <stdlib.h>
#include "mu_test.h"
#include <time.h>

UNIT(Srand_init)
srand((unsigned int)time(NULL));
END_UNIT
/************************************************************/
int IsFirstPersonLess(void *first, void *sec)
{
    if(sec==NULL || first==NULL)
    {
        return 1;
    }
    if (((Person *)first)->age < ((Person *)sec)->age)
    {
        return 1;
    }
    return 0;
}
/*************************************************************/
/*************************************************************************/
UNIT(GenericBubbleSort_One_Element_Array)
    int i;
    Person* arr[2];
    Person person1 = {213, 45, 100.33};
    Person person2 = {55, 12, 585.00};
    arr[1] = &person1; 
    arr[2] = &person2;
    GenericBubbleSort((void *)arr, 2, IsFirstPersonLess);
    for(i =0; i<1 ;++i)
    {
        ASSERT_THAT(arr[i]->age <= arr[i+1]->age);
    }
    GenericBubbleSort((void *)arr, 1, IsFirstPersonLess);
    ASSERT_THAT(arr[i]->age <= arr[i+1]->age);
    
END_UNIT

UNIT(GenericShakeSort_One_Element_Array)
int i;
    Person* arr[2];
    Person person1 = {213, 45, 100.33};
    Person person2 = {55, 12, 585.00};
    arr[1] = &person1; 
    arr[2] = &person2;
    GenericBubbleSort((void *)arr, 2, IsFirstPersonLess);
    for(i =0; i<1 ;++i)
    {
        ASSERT_THAT(arr[i]->age <= arr[i+1]->age);
    }
    GenericShakeSort((void *)arr, 1, IsFirstPersonLess);
    ASSERT_THAT(arr[i]->age <= arr[i+1]->age);
    
END_UNIT


UNIT(GBubble_Sort_Few_Inputs_Test)
    int i;
    Person* arr[12];
    Person person1 = {213, 45, 100.33};
    Person person2 = {55, 12, 585.00};
    Person person3 = {10, 23, 56.22};
    Person person4 = {213, 45, 100.33};
    Person person5 = {545, 12, 585.00};
    Person person6 = {10, 23, 56.22};
    Person person7 = {213, 45, 100.33};
    Person person8 = {5, 12, 585.00};
    Person person9 = {0, 23, 56.22};
    Person person10 = {23, 45, 100.33};
    Person person11 = {54, 12, 585.00};
    Person person12 = {44, 23, 56.22};
    arr[1] = &person1; arr[2] = &person2; arr[3] = &person3;
    arr[4] = &person4; arr[5] = &person5; arr[6] = &person6;
    arr[7] = &person7; arr[8] = &person8; arr[9] = &person9;
    arr[10] = &person10; arr[11] = &person11; arr[12] = &person12;
    
    GenericBubbleSort((void *)arr, 12, IsFirstPersonLess);
    for(i =0; i<11 ;++i)
    {
        ASSERT_THAT(arr[i]->age <= arr[i+1]->age);
    }
    /*
    puts("Bubble Sort");
    for (int i = 0; i < 12; ++i)
    {
        printf("age person %d is %d\n", i + 1, arr[i]->age);
    }*/
    END_UNIT
/*************************************************************************/
    UNIT(GShake_Sort_Few_Inputs_Test)
    int i;
        Person* arr[12];
    Person person1 = {213, 45, 100.33};
    Person person2 = {55, 12, 585.00};
    Person person3 = {10, 23, 56.22};
    Person person4 = {213, 45, 100.33};
    Person person5 = {545, 12, 585.00};
    Person person6 = {10, 23, 56.22};
    Person person7 = {213, 45, 100.33};
    Person person8 = {5, 12, 585.00};
    Person person9 = {0, 23, 56.22};
    Person person10 = {23, 45, 100.33};
    Person person11 = {54, 12, 585.00};
    Person person12 = {44, 23, 56.22};
    arr[1] = &person1; arr[2] = &person2; arr[3] = &person3;
    arr[4] = &person4; arr[5] = &person5; arr[6] = &person6;
    arr[7] = &person7; arr[8] = &person8; arr[9] = &person9;
    arr[10] = &person10; arr[11] = &person11; arr[12] = &person12;

    GenericShakeSort((void *)arr, 12, IsFirstPersonLess);
    for (i = 0; i < 1; ++i)
    {
        ASSERT_THAT(arr[i]->age <= arr[i + 1]->age);
    }
/*
puts("Shake Sort");
for (int i = 0; i < 12; ++i)
{
    printf("age person %d is %d\n", i + 1, arr[i]->age);
}*/
END_UNIT
/*************************************************************************/

/*************************************************************************/
UNIT(GBubble_Sort_Huge_Inputs_Test)
int i;
Person **arr = NULL;
arr = (Person**)malloc(500 * sizeof(Person*));

for (i=0; i < 500; ++i)
{
    arr[i] = (Person*)malloc(sizeof(Person));
}

for (i = 0; i < 500; ++i)
{
    arr[i]->age = rand()%80;
}

GenericBubbleSort((void *)arr, 500, IsFirstPersonLess);
for (i = 0; i < 499; ++i)
{
    ASSERT_THAT(arr[i]->age <= arr[i + 1]->age);
}

for (i = 0; i < 500; ++i)
{
    free(arr[i]);
}
free(arr);
END_UNIT

UNIT(GShake_Sort_Huge_Inputs_Test)
int i;
Person **arr = NULL;
arr = (Person **)malloc(500 * sizeof(Person *));

for (i = 0; i < 500; ++i)
{
    arr[i] = (Person *)malloc(sizeof(Person));
}

for (i = 0; i < 500; ++i)
{
    arr[i]->age = rand() % 80;
}

GenericShakeSort((void *)arr, 500, IsFirstPersonLess);
for (i = 0; i < 499; ++i)
{
    ASSERT_THAT(arr[i]->age <= arr[i + 1]->age);
}
/*
puts("Shake Sort");
for (int i = 0; i < 500; ++i)
{
    printf("age person %d is %d\n", i + 1, arr[i]->age);
}*/
for (i = 0; i < 500; ++i)
{
    free(arr[i]);
}
free(arr);
END_UNIT

/*************************************************************************/

TEST_SUITE(Generic Sort Tests)
TEST(GBubble_Sort_Few_Inputs_Test)
TEST(GShake_Sort_Few_Inputs_Test)
TEST(GBubble_Sort_Huge_Inputs_Test)
TEST(GShake_Sort_Huge_Inputs_Test)
TEST(GenericBubbleSort_One_Element_Array)
TEST(GenericShakeSort_One_Element_Array)
END_SUITE