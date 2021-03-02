#include <stdio.h>

int avgArr (const int* arr, int size)
{
    int sum=0;
    int i=0;
    for (i; i<size; ++i)
    {
        arr[i]+=arr[i]+5;
    }
    return sum;
}

int main ()
{
    int arr[3]={250,1,130};
    int sum = avgArr (arr, 3);
    printf ("Summ arr = %d\n.", sum);

    return 0;
}