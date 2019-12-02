#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "chunkstring.h"

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
	if (ls == -1) {
		error_handler(); return 1;
	}
	if (-1 == listen(ls, 16)) {
		error_handler(); return 1;
	}
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(7653);
	if ( -1 == bind(ls, &addr, sizeof(addr))) {
		error_handler(); return 1;
	}

	for(;;) {

	}
}
