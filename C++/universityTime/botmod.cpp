#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "botmod.hpp"

void Player::SetNum(int n) { number = n; }
void Player::SetMon(int m) { money = m; }
void Player::SetMat(int m) { material = m; }
void Player::SetProd(int p) { product = p; }
void Player::SetFac(int f) { factory = f; }
int Player::GetNum() { return number; }
int Player::GetMon() { return money; }
int Player::GetMat() { return material; }
int Player::GetProd() { return product; }
int Player::GetFac() { return factory; }


Bot::Bot()
{
	buf_used = 0;
	for (int i=0; i<INBUFSIZE; i++) {
		buf[i] = 0;
	}
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

void Bot::ShowYourStats()
{
	printf("### Show stats:\n");
	printf("###\tNum: \t%i\n", GetNum());
	printf("###\tMon: \t%i\n", GetMon());
	printf("###\tMat: \t%i\n", GetMat());
	printf("###\tProd:\t%i\n", GetProd());
	printf("###\tFac: \t%i\n", GetFac());
}

void Bot::Say(const char *s)
{
    	int len;
    	for (len=0; s[len]; len++);
    	write(sd, s, len);
		printf("###SAY:%s", s);
}

void Bot::UpdateStats()
{
	char **ppline[5], *line, sep[] = " $#:\t\n", *endptr;
	int i, n[5];
	Say("me\n");

	for(i=0; i<5; i++) {
		line = ListenStr();
		ppline[i] = make_packline(line, sep);
		n[i] = strtol(ppline[i][1], &endptr, 10);
		//packline_print(ppline[i]);
		delete[] line;
	}
	SetNum(n[0]);
	SetMon(n[1]);
	SetMat(n[2]);
	SetProd(n[3]);
	SetFac(n[4]);
	for(i=0; i<5; i++) {
		delete[] ppline[i];
	}
	//number = strtol(pline[1], NULL, 10);
}

char *Bot::ListenStr()
{
	char *line;
	int i, rr, size = -1;
	/*
	for (attempt=0;attempt<2;attempt++) {
		for (i=0; i < buf_used; i++) {
			if (buf[i] == '\n') {
				size = i;
				break;
			}
		}
		if (size == -1) {
			if (attempt == 0) {
				rr = read(sd, buf + buf_used, INBUFSIZE-buf_used);
				buf_used += rr;
				//printf("!!!!!!!!!!!!!!!attempt to read rr=%i\n\n",rr);
				//printf("BUFFER[%s]\n\n", buf);
			} else {
				//printf("!!!!!!!!!!!!!!!\n");
				return NULL;
			}
		}
	}
	*/
	for(;;) {
		for (i=0; i < buf_used; i++) {
			if (buf[i] == '\n') {
				size = i;
				break;
			}
		}
		if (size == -1) {
			rr = read(sd, buf + buf_used, INBUFSIZE-buf_used);
			buf_used += rr;
		} else {
			break;
		}
		//sleep(1); //oh nooo..
	}

	line = new char[size+1];
	memcpy(line, buf, size);
	line[size] = 0;
	memmove(buf, buf+size+1, INBUFSIZE - (size+1));
	buf_used -= (size+1);
	//DEBUG
		//printf("\nBUF[%s]\n\n", buf);
	/*
	for (i=0; i<size; i++)
		printf("%c", line[i]);
	printf("\n");
	*/
	printf("%s\n", line);
		//printf("BUFUSED after = %i\n", buf_used);
	return line;
}

void Bot::ListenUntil(const char *target)
{
	char *temp;
	for(;;) {
		temp = ListenStr();
		if (!strcmp(temp, target)) {
			delete[] temp;
			break;
		}
		delete[] temp;
	}
}

// ===========================================================
// ===========================================================
// ===========================================================
// ===========================================================
// ===========================================================
// ===========================================================
// ===========================================================
// ===========================================================


//PACKLINE
int is_it_sep(int c, const char *sep)
{   
    int i;
    for (i=0; sep[i]; i++) {
        if (c == sep[i]) {
            return 1;
        }
    }
    return 0;
}

int word_count(const char *line, const char *sep)
{
    if (line == NULL) return 0;
    int i,f=0,len, count=0;
    for(len=0; line[len]; len++);
    for (i=0;i<len;i++) {
        if (!is_it_sep(line[i], sep)) {
            f = 1;
        } else {
            if (f == 1) {
                count++;
                f = 0;
            }
        }
    }
    if (f == 1) { count++; }
    return count;
}

void packline_print(char **packline)
{
	if (packline) {
		printf("packline_print:");
		for (int i=0; packline[i]; i++) {
			printf("[%s]", packline[i]);
		}
		printf("\n");
	} else {
		printf("packline_print:NULL\n");
	}
}

int packline_size(const char **packline)
{
	int size;
	for(size=0;packline[size];size++);
	return size;
}

void packline_free(const char **packline)
{
	int size = packline_size(packline);
	for(int i=0; i<size; i++)
		delete[] packline[i];
}

char **make_packline(const char *line, const char *sep)
{
    if (line == NULL) return NULL;
    char **packline;
    char *temp;
    int i, j, f, len, size = word_count(line, sep);
    /*copy of line*/
    for(len=0; line[len]; len++);
	temp = new char[len+1];
    for(i=0; i<len+1; i++) temp[i] = line[i];
	packline = new char*[size+1];

    packline[size] = NULL;
    j = 0; f = 0;
    for (i=0;i<len;i++) {
        if (!is_it_sep(line[i], sep)) {
            if (f == 0) {
                packline[j] = &(temp[i]);
                j++;
            }
            f = 1;
        } else {
            temp[i] = 0;
            if (f) {
                f = 0;
            }
        }
    }
	return packline;
}
