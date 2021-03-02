
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
  
int main(int argc, char const *argv[])
{
    int sock = 0;
    struct sockaddr_in serv_addr;
    const char *hello = "Hello from client";
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        abort();
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
     /* 
    // Convert IPv4 and IPv6 addresses from text to binary form
    //127.0.0.1*/

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        abort();
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        abort();
    }

    while(1)
    {
        sleep(1);
        send(sock , hello , strlen(hello) , 0);
        printf("Hello message sent\n");
        read( sock , buffer, 1024);
        printf("%s\n",buffer );
    }
    close(sock);
    return 0;
}