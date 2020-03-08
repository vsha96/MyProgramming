gamemod.o: gamemod.cpp gamemod.hpp
	g++ -Wall -g -c gamemod.cpp -o gamemod.o

packline.o: packline.cpp packline.hpp
	g++ -Wall -g -c packline.cpp -o packline.o

botmod.o: botmod.cpp botmod.hpp
	g++ -Wall -g -c botmod.cpp -o botmod.o
bot: bot.cpp botmod.o packline.o
	g++ -Wall -g bot.cpp botmod.o packline.o -o bot
gameserver: gameserver.c
	gcc -Wall -g gameserver.c -o gameserver
