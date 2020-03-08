#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "botmod.hpp"
#include "packline.hpp"
//#include "gamemod.hpp"
		
int main(int argc, char **argv)
{
	Game game;
	Game &g = game;
	Bot robbie(&g); // <- &game
	
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
	robbie.ListenUntil("* GAME STARTS");
	
	robbie.UpdateStats();
	//robbie.ShowYourStats();
	robbie.UpdateMarket();
	//robbie.ShowMarket();

	robbie.Say("turn\n");


	
	for(;;) { sleep(1); }
}
