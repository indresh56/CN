#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include<string.h>

int main()
{
int ffd=open("ABC",O_RDWR);
char *buff="P.cpp";
write(ffd,buff,strlen(buff));
sleep(1);

char rbuff[100];
read(ffd,rbuff,100);
printf("%s\n",rbuff);

}
