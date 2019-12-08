#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "chunkstring.h"

#define BUFSIZE 128
#define MAX_CLIENT_FDS 128

int error_handler()
{
	perror(NULL);
	fflush(stderr);
	return 1;
}

int ServerSetup(int port, int *ls)
{
	struct sockaddr_in addr;
	*ls = socket(AF_INET, SOCK_STREAM, 0);
	if (*ls == -1)
		return error_handler();
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(port);
	if (-1 == bind(*ls, (struct sockaddr *)&addr, sizeof(addr)) ||
		-1 == listen(*ls, 16))
		return error_handler();
	return 0;
}

int main(int argc, char **argv)
{
	int ls;
	int port = 14500;
	if (!ServerSetup(port, &ls))

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
