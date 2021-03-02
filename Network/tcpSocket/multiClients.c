
/* 
    Client side C/C++ program to demonstrate Socket programming
*/

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 5000

#define CLIENTS_NUMBER 500

int main(int argc, char const *argv[])
{
    int sock[1024];
    

    struct sockaddr_in serv_addr;
    char* hello[CLIENTS_NUMBER];

    char buffer[1024] = {0};
    int i=0;
    

    hello[0] = "Hello from client 1";
    hello[1] = "Hello from client 2";
    hello[2] = "Hello from client 3";



    memset(sock, -1, sizeof(int)*10);


    for(i = 0; i < CLIENTS_NUMBER; ++i)
    {
        if ((sock[i] = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            printf("\n Socket creation error \n");
            abort();
        }

        printf("sock[%d] = %d\n",i,sock[i]);
    }
    



    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    /*if(inet_pton(AF_INET, "192.168.0.179", &serv_addr.sin_addr)<=0) */
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)     
    {
        printf("\nInvalid address/ Address not supported \n");
        abort();
    }
    
    for(i = 0; i < CLIENTS_NUMBER; ++i)
    {
        if (connect(sock[i], (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            printf("\nConnection Failed \n");
            abort();
        }
    }


    while(1)
    {

        for(i=0;i<CLIENTS_NUMBER;++i)
        {
            send(sock[i] , hello[0] , strlen(hello[0]) , 0);
            printf("Hello message sent\n");
            read( sock[i] , buffer, 1024);
            printf("%s\n",buffer );
        }

    }

    for(i = 0;i < CLIENTS_NUMBER; ++i)
    {
        close(sock[i]);
    }

    return 0;
}