
#include "server.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/un.h>
#include <signal.h>
#include <sys/time.h>
#include <iterator>
#include <cassert>


using std::endl;
using std::cout;

struct Arguments{
    void* m_readBuffer;
    void* m_sendBuffer;
    size_t m_readBufferSize;
    size_t m_sendBufferSize;
};


Server::Server(uint16_t port) 
: m_master(socket(AF_INET, SOCK_STREAM, 0))
, m_clients(1024, -1)
{
    assert(m_master > 2);
    int backlog=10;

    memset(&address, 0, sizeof(struct sockaddr_in)); 

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
     
    SetAndBind(&address, sizeof(address)); 
    assert(listen(m_master, backlog) == 0);
    SetSocketToNonBlockMode(m_master);
}


Server::~Server()
{
	std::vector<int>::iterator itb = m_clients.begin();
	std::vector<int>::iterator ite = m_clients.end();
	while(itb != ite)
	{
		assert(close(*itb) == 0);
		++itb;
	}
	assert(close(m_master) == 0);
}



void Server::SetAndBind(struct sockaddr_in* address, socklen_t structSize)
{
    int optval=1;
    assert(setsockopt(m_master, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(optval)) != -1);
    assert(bind(m_master, (struct sockaddr *)address, structSize) ==0);
}



void Server::SetSocketToNonBlockMode(const int& socket)
{
    int flags;
    assert((flags = fcntl(socket, F_GETFL,0)) != -1);
 
    flags |= O_NONBLOCK;
    
    assert(fcntl(socket, F_SETFL, flags) != -1);
}


void Server::SendToSocket(const int& socket, void* msg, size_t msgsize)
{
    errno=0;
    ssize_t send_retval = send(socket , msg , msgsize , 0);
    assert(send_retval==-1 && errno != EAGAIN && errno != EWOULDBLOCK); 
}


void Server::CloseClientSocket(size_t clientIndex)
{
    std::swap(m_clients[clientIndex], m_clients.back());
    assert(close(m_clients.back()) == 0);
    m_clients.pop_back();    
}


void Server::ReadAndSendOnAllSockets(Arguments* args)
{
    for(size_t i = 0; i < m_clients.size(); ++i)
    {
        ssize_t read_retval = read(m_clients[i], args->m_readBuffer, args->m_readBufferSize);
        
        if(read_retval > 0)
        {
            printf("%s\n", (char*)(args->m_readBuffer));
            SendToSocket(m_clients[i], args->m_sendBuffer, args->m_sendBufferSize);
        }
        
        else if (read_retval == 0)
        {
            CloseClientSocket(i);
        }
    }
}




void Server::Run()
{
	size_t addrlen = sizeof(address);
	Arguments args;
	char buffer[64];
	const char* hello = "Hello From Server";
    args.m_readBuffer = buffer;
    args.m_sendBuffer = (void*)hello;
    args.m_readBufferSize = 64;
    args.m_sendBufferSize = strlen(hello);

    while(1)
    {
        errno = 0;
        
        int new_socket = accept(m_master, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        
        if(new_socket > 0)
        {
            cout<<"New_Socket_Was_Arrived"<<new_socket<<endl;
        }
        else{
        	cout<<"Master_Socket_Is_Clean"<<endl;
        }
        

        if(new_socket == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) 
        {
            ReadAndSendOnAllSockets(&args);

        }

        else if(new_socket >2 && errno != EAGAIN && errno != EWOULDBLOCK)
        {
        	
    		m_clients.push_back(new_socket);
    		cout<<"New Added Socket  "<<new_socket<<endl;
    		SetSocketToNonBlockMode(m_clients.back());
        	
        }

        else
        {
            perror("accept");
            abort();
        }
        usleep(25000);
    }
}


/*
typedef struct{
	int* m_master;
	struct sockaddr_in* adress;
	size_t* addrlen;
	std::vector<int>& m_clients;
	Arguments* args;
} thread_args;




void* Server::ReadThread(void* ptr)
{
	thread_args* cptr = (thread_args*)ptr;
	while(1)
    {
        errno = 0;
        
        int new_socket = accept(cptr->m_master, (struct sockaddr*)(cptr->address), (socklen_t*)(cptr->addrlen));
        
        if(new_socket > 0)
        {
            cout<<"New_Socket_Was_Arrived"<<new_socket<<endl;
        }
        else{
        	cout<<"Master_Socket_Is_Clean"<<endl;
        }
        

        if(new_socket == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) 
        {
        	//

            ReadAndSendOnAllSockets(&args);

            for(size_t i = 0; i < cptr->m_clients.size(); ++i)
		    {
		        ssize_t read_retval = read(cptr->m_clients[i], args->m_readBuffer, args->m_readBufferSize);
		        
		        if(read_retval > 0)
		        {
		            printf("%s\n", (char*)(args->m_readBuffer));
		            SendToSocket(m_clients[i], args->m_sendBuffer, args->m_sendBufferSize);
		        }
		        
		        else if (read_retval == 0)
		        {
		            CloseClientSocket(i);
		        }
		    }




        }

        else if(new_socket >2 && errno != EAGAIN && errno != EWOULDBLOCK)
        {
            m_clients.push_back(new_socket);
            cout<<"New Added Socket  "<<new_socket<<endl;
            SetSocketToNonBlockMode(m_clients.back());
        }

        else
        {
            perror("accept");
            abort();
        }
        usleep(300000);
    }
}

*/