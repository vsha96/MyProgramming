#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LEX_STR_LIMIT 128


char key_word[][16] = {
	"if",
	"for",
	"print",
	"buy",
	"sell",
	"prod",
	"build",
	"turn"
};

enum Type {
	t_kword,
	t_word,
	t_oper,
	t_string,
	t_number
};

struct List {
	char *str;
	Type type;
	int line_num;
	List *next;
};

class Lex {
		enum State {
			fsm_start,
			fsm_word,
			fsm_oper,
			fsm_string
		};
		
		
		
		char buf[LEX_STR_LIMIT];
		int buf_used;

		State state;
		List *list;
		List *end;

		void Add(char *str, Type type, int line_number);
	public:
		Lex();
		List *Analyze(char *file);
};

Lex::Lex() {
	for (int i=0; i<LEX_STR_LIMIT; i++)
		buf[i] = 0;
	buf_used = 0;

	state = fsm_start;
	list = NULL;
	end = NULL;
}

List *Lex::Analyze(char *file)
{
	FILE *f;
	char c;
	if (!(f = fopen(file, "r"))) {
		perror(file);
		return NULL;
	}
	while((c = getc(f)) != EOF) {
		printf("%c", c);
	}
	return NULL; //TODO
}


int main(int argc, char **argv) {
	
	Lex lex;
	List *lex_list;
	
	if (argc != 2) {
		printf("usage: ./lex [file_name]\n");
		return 1;
	}

	lex_list = lex.Analyze(argv[1]);
	
	
	
}




