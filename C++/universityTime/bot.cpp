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
	Bot robbie(&game); // <- &game
	
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

	robbie.WaitGameStart();
	/*AND NOW WE'RE TALKING*/
	Market m;
	for(;;)
	{
		robbie.UpdateStats();
		//robbie.ShowStats();
		robbie.UpdateMarket();
		robbie.UpdatePlayer();
		//game.ShowPlayer();
		//game.ShowMarket();

		m = game.GetMarket();

		robbie.Sell(robbie.GetProd(), m.product_price);
		robbie.Buy(m.material, m.material_price);
		robbie.Produce(robbie.GetFac());

		if(robbie.EndTurn())
			break;
	}
}
