#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

class game_info {
};

bool bot_connect() {
	return true;
}

int main(int argc, char **argv) {
	char *address, *endptr;
	int port;
	if (argc == 3) {
		//addres and port
	} else {
		printf("usage: ./bot <address> <port>\n");
		return 1;
	}
	
	port = strtol(argv[2], &endptr, 10);
    if (*endptr) {
        printf("error: wrong port\n");
        return 1;
    }
}
