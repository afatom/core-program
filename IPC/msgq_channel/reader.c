#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "channel.h"

#include <assert.h>
#include <unistd.h>

/* IMSI(%s)|MSISDN(int)|IMEI(int)|OBN(string)|MCC(int)|CT(string)|*/
/**
*IMSI - max 15 digits. 15 chars 
*MSISDN - max 15 digits.
*IMEI - ???
*OBN - Operator brand name - max 64 chars
*MCC - operator MCC - max 6 digits
*CT - call type - string - max 7 chars (including '/0')
*CD-call date - string - DD/MM/YYYY max - 11 chars
*CT - call time - HH:MM:SS 9 chars
*Duration - max 24hours call -> 24*60*60 = 86400 seconds
*Download MB - max 20 * 1000MB -20G- 5 chars max   
*Upload - MB - max 5Gb -5*1000MB - 4 chars max  
*party MSI: 8 chars
*Party Operator: 8 chars
*/

typedef struct Cdr
{
	char m_imsi[16]; char m_msidn[16]; char m_imei[16];
	char m_obn[64]; char m_mcc[8]; char m_ctype[8];
	char m_cd[8];char m_ctime[16];char m_dur[8];
	char m_dwn[8];char m_up[8];char m_pms[8];char m_pop[8];
}Cdr;

int main (int argc, char* argv[])
{
	FILE* fp = NULL;
	int counter =0;
	Cdr mcdr;
	Channel* ch = NULL;

	
	/*const char* fileName=argv[1];*/
	const char* fileName="cdr.txt";
	fp = fopen(fileName,"r+");
	if(NULL == fp)
	{
		puts("File Err");
		return 0;	
	}
	puts("sleeping...");
	sleep(1);
	ch = ChannelCreate("MSGQQ", 1024, CHANNEL_CREATE);
	rewind(fp);
	while (1)
	{
		fscanf(fp, "%s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s",
			   mcdr.m_imsi, mcdr.m_msidn, mcdr.m_imei, mcdr.m_obn, mcdr.m_mcc, mcdr.m_ctype, mcdr.m_cd,
			   mcdr.m_ctime, mcdr.m_dur, mcdr.m_dwn, mcdr.m_up, mcdr.m_pms, mcdr.m_pop);
		if (feof(fp))
		{
			break;
		}
		printf("line %d\n", ++counter);
		puts("sleeping...");
		sleep(1);
		assert(ChannelTransmit(ch, &mcdr, sizeof(mcdr)) == CHANNEL_SUCCESS);
	}
	fclose(fp);

	

	


	ChannelDestroy(&ch);

	return 0;
}
