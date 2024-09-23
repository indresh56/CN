#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
int main()
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0); // 0 given for default
    struct sockaddr_in serveaddr, clientaddr;
    serveaddr.sin_family = AF_INET;
    serveaddr.sin_port = htons(8080);
    serveaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(sfd, (struct sockaddr *)&serveaddr, sizeof(serveaddr));
    listen(sfd, 5); // 5 is the wait no
    int clientsize;
    while (1)
    {
        int nsfd = accept(sfd, (struct sockaddr *)&clientaddr, &clientsize);
        int c = fork();
        if (c > 0)
            close(nsfd);
        else
        {
            close(sfd);
            printf("Client Connected\n");
            char *buff[100]; //="Hello World";

            recv(nsfd, buff, sizeof(buff), 0);
            printf("Received from client: %s\n", buff);
            char *str = "Hello Client";
            send(nsfd, str, strlen(str), 0);
            return 0;
        }
    }
}