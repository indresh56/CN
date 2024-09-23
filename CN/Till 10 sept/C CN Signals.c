#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void fun()
{
static int i=0;
i++;
if(i==5) {signal(SIGINT,SIG_DFL);}
}
int main()
{

signal(SIGINT,fun);
int t=0;
while(1){
raise(SIGINT);
t++;
printf("%d\n",t);
}
}
