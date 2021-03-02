#ifndef __SERVER_H__
#define __SERVER_H__

#include <sys/types.h>   //setandbind function
#include <sys/socket.h>  //setandbind function
#include <arpa/inet.h>
#include <vector>
#include "wtqueue.h"
#include "nevent.h"
#include <cstdint>

typedef struct Arguments Arguments; 
class Server{

public:
	explicit Server(uint16_t port = 5000);
	~Server();
	void Run();
	void Send(int clientSock, void* msg, size_t msgsize);
	WtQueue_t<Event_ShPointer>& GetQueue();
	

private:
	int m_master;
	std::vector<int> m_clients;
	WtQueue_t<Event_ShPointer> m_queue;
	struct sockaddr_in address;
	fd_set primarySet;
	fd_set tempSet; 


	Server(const Server&);
	Server& operator= (const Server&);

	void swap(int* lhs, int* rhs);
	void SetSocketToNonBlockMode(const int& socket);
	void CloseClientSocket(size_t clientIndex);
	void SendToSocket(const int& socket, void* msg, size_t msgsize);
	void SetAndBind(struct sockaddr_in* address, socklen_t structSize);
	static void* ReadThread(void* args);
	void ReadAndSendOnAllSockets(Arguments* ptr);
};


#endif //__MC_SERVER_H__