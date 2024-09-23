#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include <stdlib.h>
#include <sys/uio.h>
#include <signal.h>
int p;
void fun(int signal) {
    printf("Received signal %d\n", getpid());
    if(p!=getpid()) exit(0);
    
}
int main()
{
    signal(SIGUSR1, fun);
    
    pid_t pgid = getpgrp(); // Get the process group ID of the current process
    printf("Process Group ID: %d\n", pgid);
    int c=fork();
    if(c<=0) while(1);
    else
    {
    p=getpid();
   // printf("%d %d\n",getpid(),getppid());
     kill(0,SIGUSR1);
     wait(NULL);
    }
    
    
}

/*
take input n;
for(i=0 to n)
{
 int c=fork();
 if(c==0)
 {
  signal(SIGUSR1,fun);
  while(1);
 }
}
kill signal
for(int i=0 to n) wait(null);
*/
