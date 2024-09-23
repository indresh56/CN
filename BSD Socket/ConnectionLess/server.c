#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in serveraddress, clientaddress;
    socklen_t addr_len = sizeof(clientaddress);
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(8080);
    serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(sfd, (struct sockaddr *)&serveraddress, sizeof(serveraddress));
    char buff[100];
    int n = recvfrom(sfd, buff, 100, 0, (struct sockaddr *)&clientaddress, &addr_len);
    buff[n] = '\0';
    printf("Received from client: %s", buff);
    char *msg = "Sent from server";
    sendto(sfd, msg, strlen(msg), 0, (struct sockaddr *)&clientaddress, addr_len);
}