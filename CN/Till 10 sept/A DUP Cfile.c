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
        //printf("Parent");
        int fd = open("outtc.txt", O_RDONLY),fd2=open("out.txt",O_RDONLY);
        char C,C2;
        ssize_t bytesRead,bytesRead2;
        while ((bytesRead = read(fd, &C, 1)) > 0&&(bytesRead = read(fd2, &C2, 1)) > 0)
        {
           if(C!=C2)
           {
           printf("Testcase Failed\n");
           return 0;
           }
           // printf("%c", C);
        }
        printf("Testcase Passed\n");
       // printf("\n");
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
