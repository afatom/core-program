
#include <stdio.h>

/*define NDEBUG 1*/

void foo(void)
{
    printf("Normal situ\n");
    #ifdef NDEBUG
    printf("I am in debug mode!\n");
    #endif
    return;
}


int main()
{
    foo();

    return 0;
}

