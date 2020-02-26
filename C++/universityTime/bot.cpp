#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "botmod.h"
		
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
	robbie.Say(cmd1);
	printf("%s\n", robbie.ListenStr());
	robbie.Say(cmd1);
	printf("%s\n", robbie.ListenStr());
	robbie.Say(cmd1);
	robbie.Say(cmde);
	
	for(;;) { sleep(1); }
}
