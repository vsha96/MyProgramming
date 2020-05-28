#include "lex.hpp"
#include "syn.hpp"

int main(int argc, char **argv) {
	
	Lex lex;
	List *lex_list;
	
	if (argc != 2) {
		printf("usage: ./main [file_name]\n");
		return 1;
	}
	
	lex_list = lex.Analyze(argv[1]);
	lex.ListPrint();
}
