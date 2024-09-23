#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include<string.h>

int main()
{
mkfifo("ABC",0666);
int ffd=open("ABC",O_RDWR);
char buff[100];
read(ffd,buff,100);

    char command[512];
    snprintf(command, sizeof(command), "g++ %s -o P", buff);
    //printf("%s",command);
system(command);
int c1=dup(STDIN_FILENO),c2=dup(STDOUT_FILENO);
int c=fork();


if(c>0)
{
wait(NULL);
dup2(0,c1);
dup2(1,c2);
        int fd2 = open("Pout.txt", O_RDONLY),fd=open("OT.txt",O_RDONLY);
        char C,C2;
        char Cbuff[100];
        
        ssize_t bytesRead,bytesRead2;
        while ((bytesRead = read(fd, &C, 1)) > 0&&(bytesRead = read(fd2, &C2, 1)) > 0)
        {
           if(C!=C2)
           {
           printf("Testcase Failed\n");
          char * T="Testcase Failed";
           write(ffd,T,strlen(T));
           return 0;
           }
        }
        if(bytesRead!=0||bytesRead2!=0)
        {printf("Testcase Failed\n");
        char * T="Testcase Failed";
           write(ffd,T,strlen(T));
          }
        else{
        printf("Testcase Passed\n");
        char * T="Testcase Passed";
          write(ffd,T,strlen(T));
           }
          
  
}
else{
int itfd=open("IT.txt",O_RDONLY);
//int poutfd=open("Pout.txt",O_WRONLY);
        int poutfd = open("Pout.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
dup2(itfd,0);
dup2(poutfd,1);
execl("./P","P",NULL);

}

}
