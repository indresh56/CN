#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <poll.h>
#include <string.h>
#include <stdlib.h>

struct message
{
	long mtype;
	char mtext[256];
};

void clearbuf(char* buf)
{
	for (int i = 0; i < 256; i++)
		buf[i] = 0;
}

int main()
{
	key_t key = ftok("chatmsgq", 65);
	if (key < 0) return -1;
	int msgid = msgget(key, 0666|IPC_CREAT);

	struct pollfd fds;
	int nfds = 1;
	memset(&fds, 0, sizeof(fds));
	fds.fd = 0;
	fds.events = POLLIN;

	struct message mess;
	mess.mtype = 1;
	ssize_t msgsz;

	int pid = getpid();
	char buf[256];
	
	printf("ID: %d\n", pid);
	clearbuf(mess.mtext);
	sprintf(mess.mtext, "#%d#", pid);
	msgsnd(msgid, &mess, sizeof(mess), 0);
	
	mess.mtype = pid;

	while (1)
	{
		if (poll(&fds, 1, 100)==1)
		{
			clearbuf(buf);
			if (read(0, buf, 256) != 0)
			{
				char a = '$';
				if (buf[0] == '%') a = '%';

				clearbuf(mess.mtext);
				sprintf(mess.mtext, "%c%d%c%s", a, pid, a, buf);
		
				mess.mtype = 1;
				msgsnd(msgid, &mess, sizeof(mess), 0);
				if (a == '%') break;
			}
		}
		
		if (msgrcv(msgid, &mess, sizeof(mess), pid, IPC_NOWAIT) > 0)
			write(1, mess.mtext, strlen(mess.mtext));
	}
}

