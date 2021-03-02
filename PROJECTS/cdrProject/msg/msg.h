#ifndef __COM_H_
#define __COM_H_

#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>

/*Control cmd*/

typedef enum CCMD {
	CCMD_PING =			1,
	CCMD_PAUSE =		2,
	CCMD_RESUME =		4,
	CCMD_SHUTDOWN =		8		
	}CCMD;


/*Data cmd*/

typedef enum DCMD {
	DCMD_PING =			1,
	DCMD_SUBQ =			2,
	DCMD_OPQ =			4,
	DCMD_SUBREP =		8,
	DCMD_OPREP =		16
			
	}DCMD;






typedef unsigned long long int ulli;

typedef struct ControlMsg{
	pid_t m_senderPid;
	CCMD m_command;
	}ControlMsg;


typedef struct DataMsg{
	pid_t m_senderPid;
	DCMD m_command;
	ulli m_subImsi;
	size_t m_mcc;
	}DataMsg;



/***********************************************************************
 * Control struct msg Details and instructions for caller:
 * *********************************************************************
 * 
 * pid_t m_senderPid: process id of the msg sender
 * int m_msg: 
 * 0 - ping msg for keepalive issues
 * 1 - Pause: pause all parsers procceses
 * 2 - Resume: resume all parsers (back to initial situation)
 * 3 - ShutDown: shut down the whole application 
 * 
 * ********************************************************************/

/***********************************************************************
 * Data struct msg Details and instructions for caller:
 * *********************************************************************
 * 
 * pid_t m_senderPid: process id of the msg sender
 * int m_msg: ty 
 * 0 - ping msg for keepalive issues
 * 1 - Pause: pause all parsers procceses
 * 2 - Resume: resume all parsers (back to initial situation)
 * 3 - ShutDown: shut down the whole application 
 * 
 * ********************************************************************/


#endif /*__COM_H_*/
