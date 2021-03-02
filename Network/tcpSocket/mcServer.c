
#define _GNU_SOURCE 
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

#include <sys/un.h>

#include <signal.h>
#include <sys/time.h>

/***********************************************************************************************/
typedef struct {
    int* m_ClientsArray;
    void* m_readBuffer;
    void* m_sendBuffer;
    size_t m_readBufferSize;
    size_t m_sendBufferSize;
    size_t* m_numOfClients;
}Arguments;


/***********************************************************************************************/
void swap(int* lhs, int* rhs)
{
    int temp = *lhs;
    *lhs = *rhs;
    *rhs = temp; 
}

/***********************************************************************************************/
void SetSocketToNonBlockMode(int* socket)
{
    int flags, retval;
    if((retval = (flags= fcntl(*socket,F_GETFL,0)))<0)
    {
        perror("fcntl get flags err");
        abort();   
    }
 
    flags |= O_NONBLOCK;
    if((retval = fcntl(*socket, F_SETFL, flags))<0)
    {
        perror("fcntl get flags err");
        abort();   
    } 
}

/***********************************************************************************************/
int CreateTcpSocket(void)
{
    int sock=-1;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        abort();
    }
    return sock;
}

/***********************************************************************************************/
void CloseClientSocket(size_t i, int* ClientsArray, size_t* numOfClients)
{
    swap(ClientsArray+i, ClientsArray + *numOfClients-1);
    if(close(ClientsArray[*numOfClients-1]) != 0)
    {
        perror("close_");
        abort();   
    }
    --(*numOfClients);    
}


/***********************************************************************************************/
void SendToSocket(int* sock, char* msg, size_t msgsize)
{
    ssize_t send_retval = send(*sock , msg , msgsize , 0);
    
    if(send_retval==-1 && (errno == EAGAIN || errno == EWOULDBLOCK)) 
    {
        perror("send");
        abort();
    }
}

/***********************************************************************************************/
void SetAndBind(int* fd, struct sockaddr_in* address, socklen_t structSize)
{
    int optval=1;
    if(setsockopt(*fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(optval))<0)
    {
        perror("SO_REUSEADDR failed");
        abort();
    }

    if (bind(*fd, (struct sockaddr *)address, structSize)<0)
    {
        perror("bind failed");
        abort();
    }
}

/***********************************************************************************************/
void ReadAndSendOnAllSockets(Arguments* args)
{
    ssize_t read_retval=0;
    size_t i=0;
    for(i = 0; i < *(args->m_numOfClients); ++i)
    {
        read_retval = read( args->m_ClientsArray[i], args->m_readBuffer, args->m_readBufferSize);
        
        if(read_retval > 0) /*close socket and delete this client*/
        {
            printf("%s\n", (char*)(args->m_readBuffer));
            SendToSocket(&(args->m_ClientsArray[i]), args->m_sendBuffer, args->m_sendBufferSize);
        }
        
        else if (read_retval == 0)
        {
            CloseClientSocket(i, &(args->m_ClientsArray[i]), args->m_numOfClients);
        }
    }
}
/***********************************************************************************************/


int main(int argc, char const *argv[])
{
    int server_fd=-1, new_socket=-1, backlog=10;
    uint16_t PORT = 5000;
    struct sockaddr_in address;
    size_t  numOfClients=0, addrlen = sizeof(address);
    int ClientsArray[1024]={0};
    Arguments args;
    char buffer[4096] = {0};
    char *hello = "Hello from server";


    server_fd = CreateTcpSocket();
    memset(&address, 0, sizeof(struct sockaddr_in)); 

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
     
    SetAndBind(&server_fd, &address, sizeof(address)); 
    if(listen(server_fd, backlog) < 0)
    {
        perror("listen");
        abort();
    }

    SetSocketToNonBlockMode(&server_fd);
    
    args.m_ClientsArray = ClientsArray;
    args.m_readBuffer = buffer;
    args.m_sendBuffer = hello;
    args.m_readBufferSize = 4096;
    args.m_sendBufferSize = strlen(hello);
    args.m_numOfClients = &numOfClients;

    while(1)
    {
        errno = 0;
        
        new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        
        if(new_socket > 0)
        {
            printf("New_Socket_Was_Arrived = %d\n", new_socket);
        }
        else{
            puts("Master_Socket_Is_Clean");
        }
        

        if(new_socket == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) 
        {
            ReadAndSendOnAllSockets(&args);

        }

        else if(new_socket >2 && errno != EAGAIN && errno != EWOULDBLOCK)
        {
            ClientsArray[numOfClients]=new_socket;
            ++numOfClients;
            printf("New Added Socket = %d\n", new_socket-1);
            SetSocketToNonBlockMode(&ClientsArray[numOfClients-1]);
        }

        else
        {
            perror("accept");
            abort();
        }
        usleep(300000);
    }

    return 0;
}