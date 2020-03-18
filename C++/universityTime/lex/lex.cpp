#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LEX_STR_LIMIT 128


char M1[] = {
	'\t',
	'\n',
	' '
};

char Op1[] = {
	'>',
	'<',
	'=',
	'!'
};

char R[] = {
	'(',
	')',
	'{',
	'}'
};


struct List {
	char *str;
	//Type type;
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
		enum Type {
			t_word,
			t_oper,
			t_string
		};
		
		
		char buf[LEX_STR_LIMIT];
		int buf_used;

		State state;
		List *list;
		List *end;

		void Add(char *str, Type type, int line_number);
	public:
		Lex();
		List Analyze(char *file);
};

Lex::Lex() {
	for (int i=0; i<LEX_STR_LIMIT; i++)
		buf[i] = 0;
	buf_used = 0;

	state = fsm_start;
	list = NULL;
	end = NULL;
}


int main() {
	
	/*
	printf("%c\n", Op1[0]);
	printf("%c\n", Op1[1]);
	printf("%lu\n", sizeof(Op1));
	*/
	
	
	
}




