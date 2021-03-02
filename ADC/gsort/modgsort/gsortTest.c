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
    if (((Person*)first)->age < ((Person*)sec)->age)
    {
        return 1;
    }
    return 0;
}
/*************************************************************/
/*************************************************************************/

UNIT(GBubble_Sort_Few_Inputs_Test)
    int i;
    Person arr[12];
    Person person1 = {213, 45, 100.33};
    Person person2 = {55, 12, 585.00};
    Person person3 = {10, 23, 56.22};
    Person person4 = {213, 45, 100.33};

    arr[1] = person1; arr[2] = person2; arr[3] = person3; arr[4] = person4; 
    
    GenericBubbleSort((void *)arr, 4, sizeof(Person), IsFirstPersonLess);

    for(i =0; i<2 ;++i)
    {
        ASSERT_THAT(arr[i].age <= arr[i+1].age);
    }
    /*
    puts("Bubble Sort");
    for (int i = 0; i < 12; ++i)
    {
        printf("age person %d is %d\n", i + 1, arr[i]->age);
    }*/
    END_UNIT
/*************************************************************************/


UNIT(_Sort_Huge_Inputs_Test)
int i;
Person *arr = NULL;
arr = (Person *)malloc(500 * sizeof(Person));


for (i = 0; i < 500; ++i)
{
    arr[i].age = rand() % 80;
}

 GenericBubbleSort((void *)arr, 500, sizeof(Person), IsFirstPersonLess);
for (i = 0; i < 499; ++i)
{
    ASSERT_THAT(arr[i].age <= arr[i + 1].age);
}
/*
puts("Shake Sort");
for (int i = 0; i < 500; ++i)
{
    printf("age person %d is %d\n", i + 1, arr[i]->age);
}*/

free(arr);
END_UNIT

TEST_SUITE(Generic Sort Tests)
TEST(GBubble_Sort_Few_Inputs_Test)
TEST(_Sort_Huge_Inputs_Test)
END_SUITE