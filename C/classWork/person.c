#include <stdio.h>

    typedef struct person
    {
        int id;
        int age;
        int edu;
    }person;
    void swappersons (person* one, person* two)
    {
        person temp;
        temp = *one;
        *one=*two;
        *two=temp;
    }
    void SortPersonArr (person* arr, int size)
    {
        for (int i=0; i<size-1; ++i)
        {
            for (int j=0; j<size-i-1; ++j)
            {
                if ((arr[j].id) > (arr[j+1].id))
                {
                    /*
                    person temp;
                    temp =arr[j];
                    arr[j]=arr[j+1];
                    arr[j+1]=temp;
                    */
                    swappersons (&arr[j], &arr[j+1]);

                }
            }
        }

    }
int main ()
{
    person arr[3];
    /*reading data*/
    for (int i=0; i<3; ++i)
    {
        printf("Enter id for person %d\n",i);
        scanf("%d", &arr[i].id);
        printf("Enter age for person %d\n",i);
        scanf("%d", &arr[i].age);
        printf("Enter edu for person %d\n",i);
        scanf("%d", &arr[i].edu);
    }
    for (int j=0; j<3; ++j)
    {
        printf("Person %d Data:\n",j+1);
        printf("id = %d\n", arr[j].id);
        printf("age = %d\n", arr[j].age);
        printf("edu = %d\n", arr[j].edu);
    }

    SortPersonArr (arr,3);
        for (int j=0; j<3; ++j)
    {
        printf("Person %d Data:\n",j+1);
        printf("id = %d\n", arr[j].id);
        printf("age = %d\n", arr[j].age);
        printf("edu = %d\n", arr[j].edu);
    }

    return 0;
}