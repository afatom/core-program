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
	
	if ((msqid = msgget(qkey, 0) == -1))
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
    

	
	 msgrcv(msqid, (void *)msgp_1, sizeof(msgp_1->mtext), 1, 0);

    
	/*****************************************************************/
    
    printf("msg.txt:: %s\n", msgp_1->mtext);
    
    

	msgctl(msqid, IPC_RMID, NULL);
	
	
return 0;
}
