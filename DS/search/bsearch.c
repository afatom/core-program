#include <stdio.h>
#include <stdlib.h>

int BinarySearchIterative(int* _arr, size_t _size, int _element);
int BinarySearchRec(int* _arr, size_t _size, int _element);
int InterpolationSearch(int* _arr, size_t _size, int _element);

int main(int argc, char const *argv[])
{
  /* code */
  int arr[10]={1,2,3,4,5,6,7,8,9,10};
  int index = BinarySearchIterative(arr, 10, 5);
  printf("iter index = %d\n",index);
  index = BinarySearchRec(arr,10,5);
  printf("rec index = %d\n",index);
  return 0;
}



int BinarySearchIterative(int* _arr, size_t _size, int _element)
{
    int leftIndex = 0, rightIndex = _size-1, midIndex = _size/2;
    if(_arr == NULL || _size == 0)
    {
        return -1;
    }
    while(leftIndex < rightIndex)
    {
        if(_arr[midIndex] == _element)
        {
            return midIndex;
        }
        else if (_arr[midIndex] < _element)
        {
            /*incr left*/
            leftIndex = midIndex + 1;
            midIndex = (rightIndex + leftIndex)/2;
        }
        else 
        {
            rightIndex = midIndex - 1;
            midIndex = (rightIndex + leftIndex)/2;
        }
    }
    return (_arr[leftIndex] == _element) ? (leftIndex) : (-1);
}

int BinarySearchRec(int* _arr, size_t _size, int _element)
{
    int index;
    if(_size == 0 || NULL ==_arr)
    {
        return -1;
    }
    /*
    if(_size/2 == 0)
    {
        return -1;
    }*/
    if(_arr[_size/2] == _element)
    {
        return _size/2;
    }
    if (_arr[_size/2] < _element)
    {
        index = BinarySearchRec(_arr + _size/2 + 1, _size - _size/2 -1, _element);
    }
    else
    {
        return BinarySearchRec(_arr,_size/2, _element);
    }
    return ((index != -1) ? (_size/2+1+index):(-1));
}
