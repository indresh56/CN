#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include<string.h>

int main()
{
int ffd=open("ABC",O_RDWR);
char *buff="P.cpp";
int fd=open("P.cpp",O_RDONLY);
char C;
ssize_t bytesRead;
while(( bytesRead=read(fd,&C,1))>0)
{
write(ffd,&C,1);
}
write(ffd,"@",1);
//write(ffd,buff,strlen(buff));
//sleep(2);
int ffd2=open("DEF",O_RDWR);
//wait(NULL);
char rbuff[100];
read(ffd2,rbuff,100);
printf("%s\n",rbuff);


}
