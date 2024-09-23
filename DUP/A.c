#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main()
{
    int c = 0;
    int fdin = open("intc.txt", O_RDONLY);
    int fdout = open("out.txt", O_WRONLY);
    c = fork();
    if (c > 0)
    {
        wait(NULL);
        // printf("Parent");
        int fd = open("out.txt", O_RDONLY);
        char C;
        ssize_t bytesRead;
        while ((bytesRead = read(fd, &C, 1)) > 0 && C != '\n')
        {
            printf("%c", C);
        }
        printf("\n");
        /* read(fd, &C, 1);
         // while (C != '\n')
         {
             printf("%c", C);
             // read(fdout, &C, 1);
         }*/
    }
    else
    {
        dup2(fdin, 0);
        dup2(fdout, 1);
        execl("./P.exe", "P.exe", NULL);
        close(fdin);
        close(fdout);
    }
}