#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include<string.h>
int main()
{
mkfifo("Server",0666);

int fd=open("Server",O_RDONLY);
char * msgfd[100];
int n=0;
//int c=fork();
//if(c>0)

while(1)
{
 char msg[100];
 ssize_t bytesRead=read(fd,msg,100);
 if(bytesRead<=0) {continue;}
 printf("%s\n",msg);
 if(strlen(msg)>3&&msg[0]=='P'&&msg[1]=='I'&&msg[2]=='D')
 {
   mkfifo(msg+3,0666);
   msgfd[n]=msg+3;
   n++;
  
  printf("%s\n",msg);
 }
 else{
 int l=0;
 char str[30];
 while(l<100&&msg[l]!=' ') 
 {
  str[l]=msg[l];
  l++;
 }
 l++;
 
 for(int i=0;i<n;i++)
 {
 //printf("%s %d",msg,msgfd[i]);
  if(strcmp(msgfd[i],str)!=0)
  {
   int ssd=open(msgfd[i],O_WRONLY);
  write(ssd,msg+l,strlen(msg)-l);
  }
 }
 }
}


}
