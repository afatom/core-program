#include <stdio.h>

#pragma pack(push, 1) // exact fit - no padding
typedef struct MyStruct2
{
    char b;
    int a;
    int array[2];
} MyStruct2;
#pragma pack(pop) //back to whatever the previous packing mode was

typedef struct MyStruct1
{
    char b;
    int a;
    int array[2];
} MyStruct1;

int main ()
{

    printf("With alginments: size of struct is %lu\n", sizeof(MyStruct1));
    printf("With No alginments: size of struct is %lu\n", sizeof(MyStruct2));

    return 0;
}