#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int g_var = 10;

int main (int argc, char* argv[])
{
    int i =0;
    int l_var = 20;
    pid_t n,id,pid,ppid,uid,gid,euid,egid;

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
            printf("Parent Proc Id::%lu.\n",(size_t)getpid());
            printf("Parent of Parent Proc Id::%lu.\n",(size_t)getppid());
            printf("UID of Parent Proc ::%lu.\n",(size_t)getuid());
            printf("GID of Parent Proc ::%lu.\n",(size_t)getgid());
	        printf("EUID of Parent Proc ::%lu.\n",(size_t)geteuid());
            printf("EGID of Parent Proc ::%lu.\n",(size_t)getegid());
 						           
         
            
            sleep(20);
            
        }
    }
    else {
        for(i = 0; i<30;++i)
        {
            --g_var;
            printf("Child gvar : %d\n",g_var);
            --l_var;
            printf("child lvar : %d\n",l_var);
            printf("child Proc Id::%lu.\n",(size_t)getpid());
            printf("Parent of child Proc Id::%lu.\n",(size_t)getppid());
            printf("UID of child Proc ::%lu.\n",(size_t)getuid());
            printf("GID of child Proc ::%lu.\n",(size_t)getgid());
	        printf("EUID of child Proc ::%lu.\n",(size_t)geteuid());
            printf("EGID of child Proc ::%lu.\n",(size_t)getegid());
            sleep(15);
        }
    }

    return 0;

}
