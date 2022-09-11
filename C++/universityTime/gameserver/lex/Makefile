syn.o: syn.hpp syn.cpp
	g++ -Wall -g -c syn.cpp -o syn.o
lex.o: lex.hpp lex.cpp
	g++ -Wall -g -c lex.cpp -o lex.o
main: main.cpp lex.o syn.o
	g++ -Wall -g main.cpp lex.o -o main
