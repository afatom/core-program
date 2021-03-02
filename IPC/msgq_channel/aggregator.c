#include "channel.h"
#include <time.h>       /*srand*/
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <assert.h>
   
#include <stdio.h>
#include <unistd.h>

typedef struct RxCdr
{
	char m_imsi[16];
	char m_msidn[16];
	char m_imei[16];
	char m_obn[64];
	char m_mcc[8];
	char m_ctype[8];
	char m_cd[8];
	char m_ctime[16];
	char m_dur[8];
	char m_dwn[8];
	char m_up[8];
	char m_pms[8];
	char m_pop[8];
} RxCdr;

int main (void)
{
	int i=0;
	Channel* ch;
	RxCdr pMsg;
	ch = ChannelCreate("MSGQQ", 1024, CHANNEL_CREATE);
	while (ChannelReceive(ch, &pMsg, sizeof(pMsg)) == CHANNEL_SUCCESS)
	{

		/*assert(ChannelReceive(ch, &pMsg, sizeof(pMsg)) == CHANNEL_SUCCESS);*/
		printf("printing line # %d\n",++i);
		fprintf(stdout, "%s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s",
				pMsg.m_imsi, pMsg.m_msidn, pMsg.m_imei, pMsg.m_obn, pMsg.m_mcc, pMsg.m_ctype, pMsg.m_cd,
				pMsg.m_ctime, pMsg.m_dur, pMsg.m_dwn, pMsg.m_up, pMsg.m_pms, pMsg.m_pop);

		sleep(1);
		
	}
	ChannelDestroy(&ch);

	return 0;
}
