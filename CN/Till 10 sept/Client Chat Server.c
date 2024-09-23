#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include<string.h>
int main()
{
int ffd=open("Server",O_RDWR);

int pd=getpid();
//char buff[20];
char nbuff[20];
sprintf(nbuff,"%d",pd);
//write(wfd,nbuff,strlen(nbuff));
char Start[100];
sprintf(Start,"PID%d",pd);
write(ffd,Start,strlen(Start));
int c=fork();
if(c>0)
{
while(1)
{
char msg[100];
scanf("%s",msg);
char nmsg[120];
sprintf(nmsg,"%s %s",nbuff,msg);
write(ffd,msg,100);
}
}
else{

while(1)
{
char msg[100];
int nfd=open(nbuff,O_RDONLY);
read(nfd,msg,100);

if (nfd < 0) {
	continue;
}

printf("Message received: %s\n",msg);
}
}
}
