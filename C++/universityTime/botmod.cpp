#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "botmod.h"

void Player::SetNum(int n) { number = n; }
void Player::SetMon(int m) { money = m; }
void Player::SetMat(int m) { material = m; }
void Player::SetProd(int p) { product = p; }
void Player::SetFac(int f) { factory = f; }

Bot::Bot()
{
	SetNum(-1);
	SetMon(10000);
	SetMat(4);
	SetProd(2);
	SetFac(2);
}

bool Bot::BotConnect(char *address, char *str_port)
{
	struct sockaddr_in addr;
	int port;
	char *endptr;
	port = strtol(str_port, &endptr, 10);
    if (*endptr) {
        printf("err: wrong port\n");
        return false;
    }
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if (!inet_aton(address, &(addr.sin_addr))) {
		printf("err: wrong address\n");
        return false;
	}
	printf("addr[%s] port[%i]\n", address, port);
	//connection
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("err: socket can't be open\n");
        return false;
	}
	printf("sd[%i]\n", sd);
	if (-1 == connect(sd, (sockaddr*) &addr, sizeof(addr))) {
		printf("err: unable to connect\n");
		return false;
	}
	printf("###connection is established!\n");

	return true;
}

void Bot::Say(char *s)
{
    	int len;
    	for (len=0; s[len]; len++);
    	write(sd, s, len);
		printf("[%s]", s);
}

char *Bot::ListenStr()
{
	// same thing in serv with memmov and memcopy
	// use buf
	// or just use &&
	//    i mean: (c1 && c2) && c3 == c1 && c2 && c3
	char c, *temp = NULL;
	int size, i;
	for (size=0; size<INBUFSIZE; size++) {
		read(sd, &c, 1);
		buf[size] = c;
		if (c == '\n') {
			buf[size] = 0;
			break;
		}
	}

	if (size == INBUFSIZE) {
		printf("Bot::ListenStr error!\n");
		return NULL;
	}
	
	temp = new char[size];
	for (i=0; i<size; i++)
		temp[i] = buf[i];

	return temp;
}
