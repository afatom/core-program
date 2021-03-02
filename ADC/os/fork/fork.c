#include <stdio.h>
#include <unistd.h>

int g_var = 10;

int main (int argc, char* argv[])
{
    int i =0;
    int l_var = 20;
    pid_t n ;

    n = fork();
    if(n<0)
    {
        /*Error*/
    }
    else if(n>0)
    {   /*Parent proc*/
        for(i = 0; i<30;++i)
        {
            ++g_var;
            printf("parent gvar : %d\n",g_var);
            ++l_var;
            printf("parent lvar : %d\n",l_var);
            sleep(15);
        }
    }
    else {
        for(i = 0; i<30;++i)
        {
            --g_var;
            printf("Child gvar : %d\n",g_var);
            --l_var;
            printf("child lvar : %d\n",l_var);
            sleep(15);
        }
    }

    return 0;

}
