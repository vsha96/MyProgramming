#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "chunkstring.h"

#define BUFSIZE 128
#define MAX_CLIENT_FDS 128

void error_handler()
{
	perror(NULL);
	fflush(stderr);
}

int main()
{
	int ls;
	struct sockaddr_in addr;
	ls = socket(AF_INET, SOCK_STREAM, 0);
	if (ls == -1)
	{
		error_handler(); return 1;
	}
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(7777);
	if ( -1 == bind(ls, (struct sockaddr *)&addr, sizeof(addr)))
	{
		error_handler(); return 1;
	}
	if (-1 == listen(ls, 16))
	{
		error_handler(); return 1;
	}
	for(;;)
	{
		int fd, fds[MAX_CLIENT_FDS];
		fd_set readfds, writefds;
		int max_d = ls;
		FD_ZERO(&readfds);
		FD_ZERO(&writefds);
		FD_SET(ls, &readfds);
		/* TODO */
		pause();
	}
}
