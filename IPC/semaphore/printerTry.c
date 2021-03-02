#include <stdio.h> 		/*printf*/
#include <sys/types.h> /**/
#include <sys/ipc.h>
#include <sys/sem.h>




int main (int argc, char* argv[])
{
	struct sembuf sops[2];
	int semid;

	/* Code to set semid omitted */

	sops[0].sem_num = 0;        /* Operate on semaphore 0 */
	sops[0].sem_op = 0;         /* Wait for value to equal 0 */
	sops[0].sem_flg = 0;

	sops[1].sem_num = 0;        /* Operate on semaphore 0 */
	sops[1].sem_op = 1;         /* Increment value by one */
	sops[1].sem_flg = 0;

	if (semop(semid, sops, 2) == -1) 
	{
	   perror("semop");
	   exit(EXIT_FAILURE);
	}
	

	return 0;
}



