#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifndef LEX_STR_LIMIT
#define LEX_STR_LIMIT 128
#endif

char key_word[][16] = {
	"if",
	"then",
	"for",
	"from",
	"to",
	"print",
	"buy",
	"sell",
	"prod",
	"build",
	"turn"
};

char separator[] = {
	' ',
	',',
	';',
	'\t',
	'\n'
};

enum Type {
	t_kword,
	t_word,
	t_oper,
	t_string,
	t_number,
	t_algebra
};

struct List {
	const char *str;
	Type type;
	int line_num;
	List *next;
};

class Lex {
		enum State {
			fsm_start,
			fsm_word,
			fsm_oper,
			fsm_string,
			fsm_number,
			fsm_algebra
		};
		
		char buf[LEX_STR_LIMIT];
		int buf_used;

		FILE *file;
		State state;
		int line_num;
		List *list; //this must be returned by Analyze
		List *end;
		
		bool BufPut(char c);
		//если никуда не подошло - то не может быть такого символа
		bool Separator(char c);
		bool MachineWord(char c);
		bool MachineOper(char c);
		bool MachineString(char c);
		bool MachineAlgebra(char c);
		bool MachineNumber(char c);
		void Add(const char *str, Type type);
		bool Pop();
		void Step(char c);
	public:
		Lex();
		List *Analyze(char *file);
		void ListPrint();
};

bool Lex::BufPut(char c)
{
	if (buf_used >= LEX_STR_LIMIT) {
		printf("ERR: BufPut: buffer is overloaded!\n");
		return false;
	}
	buf[buf_used] = c;
	buf_used++;
	return true;
}

bool Lex::Separator(char c)
{
	if (c == '\n')
		line_num++;
	return
		(c == '\t') ||
		(c == '\n') ||
		(c == ' ');
}

bool Lex::MachineWord(char c)
{
	if (state == fsm_word) {
		return 
			(c > 'a' && c < 'z') ||
			(c > 'A' && c < 'Z') ||
			(c > '0' && c < '9');
	} else if (state == fsm_start) {
		return 
			(c > 'a' && c < 'z') ||
			(c > 'A' && c < 'Z');
	} else {
		printf("ERR: MachineWord: wrong state change\n");
		return false;
	}
}

bool Lex::MachineOper(char c)
{
	if (state == fsm_oper) {
		return (c == '=');
	} else if (state == fsm_start) {
		return
			(c == '>') ||
			(c == '<') ||
			(c == '!') ||
			(c == '=');
	} else {
		printf("ERR: MachineOper: wrong state change\n");
		return false;
	}
}

bool Lex::MachineString(char c)
{
	if (state == fsm_start) {
		return (c == '"');
	} else if (state == fsm_string) {
		return (c == '"');
	} else {
		printf("ERR: MachineOper: wrong state change\n");
		return false;
	}
}

bool Lex::MachineAlgebra(char c)
{
	if (state == fsm_start) {
		return
			(c == '+') ||
			(c == '-') ||
			(c == '*') ||
			(c == '/') ||
			(c == '%');
	} else {
		printf("ERR: MachineAlgebra: wrong state change\n");
		return false;
	}
}

bool Lex::MachineNumber(char c)
{
	if ((state == fsm_start) || (state == fsm_number)) {
		return
			(c >= '0' && c <= '9');
	} else {
		printf("ERR: MachineNumber: wrong state change\n");
		return false;
	}

}

void Lex::Add(const char *str, Type type)
{
	List **temp;
	if (!strlen(str)) {
		printf("WARN: Add: you're trying to add empty string\n");
		return;
	}
	
	if (end)
		temp = &(end->next);
	else
		temp = &list;
	//printf("i am still alive\n");
	/*
	while (*temp) {
			temp = &((*temp)->next);
	}
	*/
	(*temp) = new List;
	(*temp)->str = str;
	(*temp)->type = type;
	(*temp)->line_num = line_num;
	(*temp)->next = NULL;
	end = *temp;
}

bool Lex::Pop()
{
	char *line;
	Type t;
	if (buf_used == 0)
		return false;
	
	line = new char[buf_used+1];
	memcpy(line, buf, buf_used);
	line[buf_used] = 0;
	//printf("str [%s]\n", line);
	buf_used = 0;
	switch(state)
	{
		case fsm_start:
			return true;
		case fsm_word:
			t = t_word;
			break;
		case fsm_oper:
			t = t_oper;
			break;
		case fsm_string:
			t = t_string;
			break;
		case fsm_number:
			t = t_number;
			break;
		case fsm_algebra:
			t = t_algebra;
			break;
	}
	Add(line, t);
	return true;
}

void Lex::Step(char c)
{
	switch(state)
	{
		case fsm_start: //TODO
			Pop();
			if (MachineWord(c)) {
				BufPut(c);
				state = fsm_word;
			}
				
			break;
		case fsm_word:
			if (MachineWord(c))
				BufPut(c);
			break;
		case fsm_oper:
			break;
		case fsm_string:
			break;
		case fsm_number:
			break;
		case fsm_algebra:
			break;
	}
}

Lex::Lex() {
	for (int i=0; i<LEX_STR_LIMIT; i++)
		buf[i] = 0;
	buf_used = 0;
	
	file = NULL;
	state = fsm_start;
	line_num = 1;
	list = NULL;
	end = NULL;
}

List *Lex::Analyze(char *f)
{
	char c;
	if (!(file = fopen(f, "r"))) {
		perror(f);
		return NULL;
	}
	while((c = getc(file)) != EOF) {
		Step(c);
		//printf("%c", c);
		//if (!BufPut(c)) //delete list
		//	return NULL;
	}
	ListPrint();
	fclose(file);
	return list;
}

void Lex::ListPrint()
{
	List *t;
	t = list;
	if (!t) {
		printf("WARN: ListPrint: list is empty\n");
	} else {
		while(t) {
			switch (t->type) {
				case t_kword:
					printf("t_kword");
					break;
				case t_word:
					printf("t_word  ");
					break;
				case t_oper:
					printf("t_oper  ");
					break;
				case t_string:
					printf("t_string");
					break;
				case t_number:
					printf("t_number");
					break;
				case t_algebra:
					printf("t_algebra");
					break;
			};
			printf("\t%i\t[%s]\n", t->line_num, t->str);
			t = t->next;
		}		
	}
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




