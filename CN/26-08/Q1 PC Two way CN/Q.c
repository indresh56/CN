#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include<string.h>
void par_fun(int rfd,int wfd)
{
 while(1)
 {
  char buff[100],buff2[100];
  scanf("%s",buff);
  if(strlen(buff)==0) break;
  write(wfd,buff,100);
  read(rfd,buff2,100);
  printf("Parent process read: %s\n",buff2);
  
 }
}
void child_fun(int rfd,int wfd)
{
 while(1)
 {
  char buff[100],buff2[100];
    read(rfd,buff2,100);
  printf("Child process read: %s\n",buff2);
  scanf("%s",buff);
  if(strlen(buff)==0) break;
  write(wfd,buff,100);

  
 }
}

int main()
{
 int pp1[2],pp2[2];
 pipe(pp1);
 pipe(pp2);
 
 int c=fork();
 if(c>0)
 {
 close(pp1[0]);
 close(pp2[1]);
 par_fun(pp2[0],pp1[1]);
 }
 else{
 close(pp1[1]);
 close(pp2[0]);
 child_fun(pp1[0],pp2[1]);
 
 }
}
