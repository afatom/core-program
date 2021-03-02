#include <stdio.h>

void foo (int a)
{
    if (a>0)
    {
      return 3;
    }
    return;
}

int main(int argc, char const *argv[])

{
  foo(5);
  return 0;
}
