#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serveraddress;
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(8080);
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(sfd, (struct sockaddr *)&serveraddress, sizeof(serveraddress));
    socklen_t addr_len = sizeof(serveraddress);
    char buff[100];
    char *msg = "Sent from client";
    sendto(sfd, msg, strlen(msg), 0, (struct sockaddr *)&serveraddress, sizeof(serveraddress));

    int n = recvfrom(sfd, buff, 100, 0, (struct sockaddr *)&serveraddress, &addr_len);
    buff[n] = '\0';
    printf("Received from server: %s", buff);
}