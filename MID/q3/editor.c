#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <poll.h>

int main()
{
    // mkfifo("Rep1", 0666);
    if (mkfifo("Rep1", 0666) == -1)
    {
        perror("Error creating R1 FIFO");
        return 1;
    }
    mkfifo("Rep2", 0666);
    mkfifo("Rep3", 0666);
    int rfd[3];
    rfd[0] = open("Rep1", O_RDWR);
    printf("%d", rfd[0]);
    rfd[1] = open("Rep2", O_RDWR);
    rfd[2] = open("Rep3", O_RDWR);
    struct pollfd prfd[3];
    for (int i = 0; i < 3; i++)
    {
        prfd[i].fd = rfd[i];
        prfd[i].events = POLLIN;
    }
    while (1)
    {
        int a = poll(prfd, 3, 100);
        if (a > 0)
        {
            for (int i = 0; i < 3; i++)
            {
                if (prfd[i].revents & POLLIN)
                {
                    char s[200];
                    ssize_t bytesRead = read(prfd[i].fd, s, 200);
                    if (bytesRead <= 0)
                    {
                        continue;
                    }
                    // read(prfd[i].fd, s, sizeof(s));
                    else
                    {
                        // s[bytesRead] = '\0';
                        // printf("hell");
                        printf("%s\n", s);
                    }
                }
            }
        }
    }
}