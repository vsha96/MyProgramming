botmod.o: botmod.cpp botmod.hpp
	g++ -Wall -g -c botmod.cpp -o botmod.o
bot: bot.cpp botmod.o
	g++ -Wall -g bot.cpp botmod.o -o bot
gameserver: gameserver.c
	gcc -Wall -g gameserver.c -o gameserver
