#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define INBUFSIZE 128

class Player {
		int number;
		int money;
		int material;
		int product;
		int factory; 	
	public:
		void SetNum(int n) { number = n; }
		void SetMon(int m) { money = m; }
		void SetMat(int m) { material = m; }
		void SetProd(int p) { product = p; }
		void SetFac(int f) { factory = f; }
	
};

class Game {
		struct list_player {
			class Player pl;
			class Player *next;
		};
		struct list_player *list;
	public:
		Game() { list = NULL; };
		~Game() {}; //TODO
};

//remake
char cmdt[] = "test\n";
char cmd1[] = "me\n";
char cmd2[] = "player\n";
char cmd3[] = "market\n";
char cmd4[] = "build";
char cmd5[] = "prod";
char cmd6[] = "buy";
char cmd7[] = "sell";
char cmde[] = "turn\n"; 

class Bot: public Player {
		int sd;
		char buf[INBUFSIZE];
	public:
		Bot() {
			// link with Game object
			// dont forget about destructor
			SetNum(-1);
			SetMon(10000);
			SetMat(4);
			SetProd(2);
			SetFac(2);
		}
		bool BotConnect(char *address, char *str_port);
		void ShowSD() { printf("my sd = [%i]\n", sd); }
		void Say(char *string);
		char *ListenStr();
		void ListenAll();
};

//put this shit in module!
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
		printf("error: unable to connect\n");
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

/*
void Bot::ListenAll()
{
	while(ListenStr())
}
*/

int main(int argc, char **argv)
{
	//Game game;
	Bot robbie; // <- &game
	
	char *address, *str_port;
	if (argc != 3) {
		printf("usage: ./bot <address> <port>\n");
		return 1;
	}
	
	address = argv[1];
	str_port = argv[2];

	if (!robbie.BotConnect(address, str_port)) {
		printf("err: unable to connect\n");
		return 1;
	}

	/*AND NOW WE'RE TALKING*/
	// intro strings 2 + 18
	int i;
	for (i=0; i<20; i++) {
		printf("%s\n", robbie.ListenStr());
	}
	//game starts 1
	robbie.Say(cmd1);
	robbie.Say(cmd1);
	printf("%s\n", robbie.ListenStr());
	robbie.Say(cmd1);
	printf("%s\n", robbie.ListenStr());
	robbie.Say(cmd1);
	robbie.Say(cmde);
	
	for(;;) { sleep(1); }
}
