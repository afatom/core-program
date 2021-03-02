#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <assert.h>
    
#include <stdio.h>    


int main (int argc, char* argv[])
{
   	key_t qkey;
   	const char *pathname = "mymsgqueue";
   	int proj_id = 'A'; 
   	int msqid; /*msg q id*/
   	
   	qkey = ftok(pathname, proj_id); /*<< generate aunique queue key*/
	
	if ((msqid = msgget(qkey, 0666|IPC_CREAT) == -1))
	{
		puts("Msgget Error");
		perror("Msgget Error");
  		exit(EXIT_FAILURE);
	}
	/*****************************************************************/
	typedef struct msgbuf_1 {
       long mtype;       /* message type, must be > 0 */
       char mtext[64];    /* message data */
   	}msgbuf_1;
        
    msgbuf_1* msgp_1;
    msgp_1 = (msgbuf_1*)malloc(1 * sizeof(msgbuf_1));
    assert(msgp_1 != NULL);
    
    msgp_1->mtype = 1; /*type one is - chars msg*/
    msgp_1->mtext = "hi i am transmitter, chars sec";
    
	/*****************************************************************/
    
 	typedef struct msgbuf_2 {
       long mtype;       /* message type, must be > 0 */
       int mnums[10];    /* message data */
   	}msgbuf_2;
        
    msgbuf_2* msgp_2;
    msgp_2 = (msgbuf_2*)malloc(1 * sizeof(msgbuf_2));
    assert(msgp_2 != NULL);
    
    msgp_2->mtype = 2; /*type 2 is - ints msg*/
    for(int i =0; i < 10 ; ++i)
    {
    	msgp_2->mnums[i] = i;
    }
	/*****************************************************************/
        
    
    puts("Sending msg 1");
    sleep(1);       
	if ((msgsnd(msqid, (void *)msgp_1, sizeof(msgp_1->mtext), 0))!=0)
	{
		puts("1_Msgsnd Error");
		perror("1_Msgsnd Error");
  		exit(EXIT_FAILURE);
	}
	puts("Sending msg 2");
	sleep(1);
	if ((msgsnd(msqid, (void *)msgp_2, sizeof(msgp_1->mnums), 0))!=0)
	{
		puts("2_Msgsnd Error");
		perror("2_Msgsnd Error");
  		exit(EXIT_FAILURE);
	}
	
	/*msgctl(msqid, IPC_RMID, NULL);*/
	
	
return 0;
}
