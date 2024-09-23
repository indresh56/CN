#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

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
	int msgid = msgget(key, 0666|IPC_CREAT);
	struct message mess;
	ssize_t n;

	char buf[256];
	int client[100];
	int c = 0;

	mess.mtype = 1;

	int iter = 0;	
	while (1)
	{
		clearbuf(mess.mtext);
		int n = msgrcv(msgid, &mess, sizeof(mess), 1, 0);

		if (mess.mtext == NULL) continue;
		write(1, mess.mtext, strlen(mess.mtext));
		if (mess.mtext[0] == '$')
		{
			 int id;
			 sscanf(mess.mtext, "$%d$", &id);
			 for (int i = 0; i < c; i++)
			 {
				 if (client[i] == id) continue;
				 mess.mtype = client[i];
				 msgsnd(msgid, &mess, sizeof(mess), 0);
			 }
		}
		else if (mess.mtext[0] == '#')
		{
			int id;
			sscanf(mess.mtext, "#%d#", &id);
			
			clearbuf(buf);
			sprintf(buf, "%s *JOINED*\n", mess.mtext);
			write(1, buf, strlen(buf));
				
			clearbuf(mess.mtext);
			sprintf(mess.mtext, "%s", buf);

			for (int i = 0; i < c; i++)
			{
				mess.mtype = client[i];
				msgsnd(msgid, &mess, sizeof(mess), 0);
			}

			client[c] = id;
			c++;
		}
		else if (mess.mtext[0] == '%')
		{
			int id;
			sscanf(mess.mtext, "%%%d%%", &id);

			mess.mtext[strlen(mess.mtext)-2] = '\0';

			clearbuf(buf);
			sprintf(buf, "%s *LEFT*\n", mess.mtext);
			write(1, buf, strlen(buf));

			clearbuf(mess.mtext);
			sprintf(mess.mtext, "%s", buf);
		
			int j;
			for (int i = 0; i < c; i++)
			{
				if (client[i] == id)
				{
					j = i;
					continue;
				}
				mess.mtype = client[i];
				msgsnd(msgid, &mess, sizeof(mess), 0);
			}
			
			client[j] = client[--c];
		}
		else return -1;
						
	}
	return -1;
	
	msgctl(msgid, IPC_RMID, NULL);
}	
