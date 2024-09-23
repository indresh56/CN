#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <iostream>
using namespace std;
int main()
{
    int fd = open("Rep1", O_WRONLY);
    char s[200];
    fgets(s, sizeof(s), stdin);
    // cout << s << endl;
    printf("%d", fd);
    dup2(fd, 1);
    printf("%s", s);
    close(fd);
    // write(fd, s, sizeof(s));
}