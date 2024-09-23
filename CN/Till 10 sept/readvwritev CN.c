#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include <stdlib.h>
#include <sys/uio.h>
int main()
{
int fd=open("in.txt",O_RDONLY);
int fd2=open("out.txt",O_WRONLY);
char buffer1[20],buffer2[20],buffer3[20];
struct iovec iovarray[3];
iovarray[0].iov_base=buffer1;
iovarray[1].iov_base=buffer2;
iovarray[2].iov_base=buffer3;
iovarray[0].iov_len=20;
iovarray[1].iov_len=20;
iovarray[2].iov_len=20;

readv(fd,iovarray,3);
writev(fd2,iovarray,3);
}
