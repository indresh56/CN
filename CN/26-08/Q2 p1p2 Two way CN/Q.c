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

int main()
{
 int pp1[2],pp2[2];
 pipe(pp1);
 pipe(pp2);
 
 int c=fork();
 if(c>0)
 {
  
 }
 else{
  printf("I am process P2");
  execl("./P.exe","P.exe",NULL);
 }

}
