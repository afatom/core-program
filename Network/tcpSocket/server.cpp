//#define _GNU_SOURCE 

#include <cunistd>
#include <sys/socket.h>
#include <cstdlib>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstring>
#include <climits.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <poll.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>



void swap(int* lhs, int* rhs)
{
    int temp = *lhs;
    *lhs = *rhs;
    *rhs = temp; 
}




void MCServer::SetSocketToNonBlockMode()
{
	int flags;
	if((int retval = (flags= fcntl(,F_GETFL,0)))<0)
    {
        perror("fcntl get flags err");
        abort();   
    }
 
    int flags |= O_NONBLOCK;
    if((retval = fcntl(fdSocket, F_SETFL, flags))<0)
    {
        perror("fcntl get flags err");
        abort();   
    } 
}


int MCServer::MCServer()
{
    if ((m_master = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        abort();
    }
    return fd;
}



















int main(int argc, char const *argv[])
{
    int optval=1, server_fd=-1, new_socket=-1, backlog=10, retval=0, flags=0;
    uint16_t PORT = 5000;
    struct sockaddr_in address;
    size_t i=0;
    int ClientsArray[1024]={0};
    size_t numOfClients=0;
    ssize_t read_retval=0, send_retval=0;

    size_t addrlen = sizeof(address);
    
    char buffer[4096] = {0};
    char *hello = "Hello from server";
    /**
    fd_set rfds;
    struct timeval tv;**/

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        abort();
    }

    memset(&address, 0, sizeof(struct sockaddr_in)); 
      
   /*  Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }*/
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
     
    
    if(setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optval, sizeof(optval))<0)
    {
        perror("SO_REUSEADDR failed");
        abort();
    }

    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        abort();
    }

    if (listen(server_fd, backlog) < 0)
    {
        perror("listen");
        abort();
    }

    if((retval = (flags= fcntl(server_fd,F_GETFL,0)))<0){
        perror("fcntl get flags err");
        abort();   
    }
 
    flags |= O_NONBLOCK;
    if((retval = fcntl(server_fd, F_SETFL, flags))<0)
    {
        perror("fcntl get flags err");
        abort();   
    }
    

    while(1)
    {
        errno = 0;
        new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        printf("New_Socket_Was_Arrived = %d\n", new_socket);

        if(new_socket == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) /*no new clents on the other side*/
        {
            for(i = 0; i<numOfClients; ++i)
            {
                read_retval = read( ClientsArray[i] , buffer, 4096);
                
                if(read_retval > 0) /*close socket and delete this client*/
                {
                    printf("%s\n",buffer );
                    send_retval = send(ClientsArray[i] , hello , strlen(hello) , 0);
                    
                    if(send_retval==-1 && (errno == EAGAIN || errno == EWOULDBLOCK)) /*close socket and delete this client*/
                    {
                        perror("send");
                        abort();
                    }
                }
                /*else if (read_retval == -1 && errno != EAGAIN && errno!=EWOULDBLOCK)*/
                else if (read_retval == 0)
                {
                    swap(&ClientsArray[i], &ClientsArray[numOfClients-1]);
                    if(close(ClientsArray[numOfClients-1]) != 0)
                    {
                        perror("close_");
                        abort();   
                    }
                    --numOfClients;
                }
            }
        }

        else if(new_socket >2 && errno != EAGAIN && errno != EWOULDBLOCK)
        {
            ClientsArray[numOfClients]=new_socket;
            ++numOfClients;
            printf("New Client was added = %d\n", new_socket-1);
            printf("Num of clients = %lu\n", numOfClients);


            if((retval = (flags= fcntl(ClientsArray[numOfClients-1],F_GETFL,0)))<0)
            {
                perror("fcntl get flags err");
                abort();   
            }
 
            flags |= O_NONBLOCK;
            if((retval = fcntl(ClientsArray[numOfClients-1], F_SETFL, flags))<0)
            {
                perror("fcntl get flags err");
                abort();   
            }
               
        }

        else{
            perror("accept");
            abort();
        }
        usleep(300000);
    }

    return 0;
}