#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void fun1()
{
printf("First function called\n");
}
void fun2()
{
printf("Second function called\n");
}
int main()
{

    signal(SIGUSR1, fun1);
    signal(SIGUSR2, fun2);
    int c=fork();
  if(c>0)
  {
   kill(c,SIGUSR1);
   sleep(1);
  }
  else
  {
   kill(getppid(),SIGUSR2);
   sleep(1);
  }
}
