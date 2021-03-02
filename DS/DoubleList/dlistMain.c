#include "dlist.h"
#include <stdio.h>


int main (void)
{
    int _data = 0;
    List *_list = ListCreate();
    ListPushHead(_list, 1);
    ListPushHead(_list, 2);
    ListPushHead(_list, 3);
    ListPushHead(_list, 4);
    ListPushTail(_list, 99);
    ListPushTail(_list, 100);
    ListPushTail(_list, 120);
    ListPushTail(_list, 130);
    ListPrint(_list);
    size_t noi = ListCountItems(_list);
    printf("Nodes Num = %lu \n", noi);

    ListPopHead(_list, &_data);
    printf("data = %d\n",_data);
    puts("************************");
    noi = ListCountItems(_list);
    printf("Nodes Num = %lu \n", noi);
    ListPrint(_list);

    ListPopHead(_list, &_data);

    ListPopHead(_list, &_data);
 

    ListPopHead(_list, &_data);

    printf("data = %d\n", _data);
    puts("************************");
    noi = ListCountItems(_list);
    printf("Nodes Num = %lu \n", noi);
    ListPrint(_list);

    ListDestroy(_list);
    return 0;
}