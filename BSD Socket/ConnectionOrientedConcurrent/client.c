#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
int main()
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0); // 0 given for default
    struct sockaddr_in serveaddr;
    serveaddr.sin_family = AF_INET;
    serveaddr.sin_port = htons(8080);
    serveaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(sfd, (struct sockaddr *)&serveaddr, sizeof(serveaddr));
    char *str = "Hello Server";
    send(sfd, str, strlen(str), 0);
    char buff[100];
    recv(sfd, buff, sizeof(buff), 0);
    printf("Received from Server: %s\n", buff);
}