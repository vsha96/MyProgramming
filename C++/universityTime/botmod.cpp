#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include "botmod.hpp"
#include "packline.hpp"
//#include "gamemod.hpp"

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

Game::Game()
{
	Market &m = market;
    list = NULL; m.level = -13;
	m.material = -13; m.material_price = -13;
	m.product = -13; m.product_price = -13;
};

void Game::AddPlayer(int num, int mon, int mat, int prod, int fac)
{
	list_player *p;
	p = new list_player;
	p->pl.SetNum(num);
	p->pl.SetMon(mon);
	p->pl.SetMat(mat);
	p->pl.SetProd(prod);
	p->pl.SetFac(fac);
	p->next = list;
	list = p;
}

void Game::SetPlayer(int num, int mon, int mat, int prod, int fac)
{
	list_player *temp = list;
	if (!temp) {
		AddPlayer(num, mon, mat, prod, fac);
		return;
	}

	while(temp) {
		if((temp->pl.GetNum()) == num) {
			temp->pl.SetMon(mon);
			temp->pl.SetMat(mat);
			temp->pl.SetProd(prod);
			temp->pl.SetFac(fac);
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		AddPlayer(num, mon, mat, prod, fac);
}

void Game::ShowPlayer()
{
	list_player *temp = list;
	Player p;
	printf("### Show player list:\n");
	while(temp) {
		p = temp->pl;
		printf("### Num: \t\t%i\n", p.GetNum());
		printf("###\tMon: \t%i\n", p.GetMon());
		printf("###\tMat: \t%i\n", p.GetMat());
		printf("###\tProd:\t%i\n", p.GetProd());
		printf("###\tFac: \t%i\n", p.GetFac());
		temp = temp->next;
	}
}

void Game::SetMarket(int l, int m, int mp, int p, int pp) 
{
	Market &gm = market;
    gm.level = l;
    gm.material = m; gm.material_price = mp; 
    gm.product = p; gm.product_price = pp; 
}

void Game::ShowMarket()
{
	Market &m = market;
	printf("### Market:\n");
	printf("###\tLevel:\t\t%i\n", m.level);
	printf("###\tMaterial: \t%i\n", m.material);
	printf("###\t\t\t%i $\n", m.material_price);
	printf("###\tProduction: \t%i\n", m.product);
	printf("###\t\t\t%i $\n", m.product_price);
}

Market Game::GetMarket()
{
	return market;
}

Game::~Game()
{
	list_player *target, *temp = list;
	while(temp) {
		target = temp;
		temp = temp->next;
		delete target;
	}
}

// ===========================================================
// ===========================================================
// ===========================================================

Bot::Bot(Game *g)
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
	game = g;
	game->SetMarket(-1,0,0,0,0);
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

void Bot::ShowStats()
{
	printf("### Show stats:\n");
	printf("###\tNum: \t%i\n", GetNum());
	printf("###\tMon: \t%i\n", GetMon());
	printf("###\tMat: \t%i\n", GetMat());
	printf("###\tProd:\t%i\n", GetProd());
	printf("###\tFac: \t%i\n", GetFac());
}

void Bot::ShowMarket()
{
	game->ShowMarket();
}

void Bot::Say(const char *s)
{
    	int len;
    	for (len=0; s[len]; len++);
    	write(sd, s, len);
		printf("%s", s);
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
}

void Bot::UpdateMarket()
{
	char **ppline[5], *line, sep[] = " $#:=><\t\n", *endptr;
	int i, n[5];
	Say("market\n");

	for(i=0; i<5; i++) {
		line = ListenStr();
		ppline[i] = make_packline(line, sep);
		if (i == 2 || i == 4) {
			n[i] = strtol(ppline[i][3], &endptr, 10);
		} else {
			n[i] = strtol(ppline[i][2], &endptr, 10);
		}
		//packline_print(ppline[i]);
		delete[] line;
	}

	game->SetMarket(n[0],n[1],n[2],n[3],n[4]);

	for(i=0; i<5; i++) {
		delete[] ppline[i];
	}
}

void Bot::SetPlayer(int num, int mon, int mat, int prod, int fac)
{
	game->SetPlayer(num, mon, mat, prod, fac);
}
void Bot::ShowPlayer()
{
	game->ShowPlayer();
}

void Bot::UpdatePlayer()
{
	char **ppline[5], *line, sep[] = " $#:=><\t\n", *endptr;
	int i, n[5];

	Say("player\n");

	line = ListenStr(); delete line;
	while(strcmp((line = ListenStr()),"* ===END OF PLAYERS===")) {
		delete line;
		for(i=0; i<5; i++) {
			line = ListenStr();
			ppline[i] = make_packline(line, sep);
			n[i] = strtol(ppline[i][1], &endptr, 10);
			//packline_print(ppline[i]);
			delete line;
		}
		game->SetPlayer(n[0], n[1], n[2], n[3], n[4]);
		for(i=0; i<5; i++) {
			delete ppline[i];
		}
	}
	delete line;
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

void Bot::ListenUntilPart(const char *string)
{
	char *temp;
	int n;
	for(n=0;string[n];n++);
	for(;;) {
		temp = ListenStr();
		if (!strncmp(temp, string, n)) {
			delete temp;
			break;
		}
		delete temp;
	}
}

void Bot::Produce(int count)
{
	char *line, s[256];
	sprintf(s, "%i", count);
	Say("prod "); Say(s); Say("\n");
	line = ListenStr();
	delete line;
}

void Bot::Buy(int count, int price)
{
	char *line, s[2][256];
	sprintf(s[0], "%i", count);
	sprintf(s[1], "%i", price);
	Say("buy "); Say(s[0]); Say(" "); Say(s[1]); Say("\n");
	line = ListenStr();
	delete line;
}

void Bot::Sell(int count, int price)
{
	char *line, s[2][256];
	sprintf(s[0], "%i", count);
	sprintf(s[1], "%i", price);
	Say("sell "); Say(s[0]); Say(" "); Say(s[1]); Say("\n");
	line = ListenStr();
	delete line;
}

void Bot::Build(int count)
{
	char *line, s[256];
	sprintf(s, "%i", count);
	Say("build "); Say(s); Say("\n");
	line = ListenStr();
	delete line;
}

void Bot::EndTurn()
{
	char *line;
	Say("turn\n");
	line = ListenStr();
	delete line;
	//TODO
	/*
		THERE WE MAY COLLECT INFO ABOUT AUCTIONS
	*/
	ListenUntilPart("# MONTH");
}

Bot::~Bot() {}

// ===========================================================
