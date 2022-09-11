#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "lex.hpp"

const char *KEY_WORD[] = {
	"if",
	"then",
	"for",
	"from",
	"to",
	"print",
	//in-game functuions
		//no parameters
	"turn",
	"my_id",
	"turn",
	"players",
	"active_players",
	"supply",
	"raw_price",
	"demand",
	"production_price",
		//one param - count
	"prod",
	"build",
		//one param - player's number
	"money",
	"raw",
	"production",
	"factories",
	"result_raw_price",
	"result_prod_bought",
	"result_prod_price",
		//two param - count, price
	"buy",
	"sell",
	//end of in-game functuions
	NULL
};

bool Lex::BufPut(char c)
{
	if (buf_used >= LEX_STR_LIMIT) {
		printf("ERR: BufPut: buffer is overloaded!\n");
		return false;
	}
	buf[buf_used] = c;
	buf_used++;
	/*DEBUG*/ //printf("[%c] was putted\n", c);
	return true;
}

bool Lex::IsSeparator(char c)
{
	return
		(c == '\t') ||
		(c == '\n') ||
		(c == ' ');
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

void Lex::CheckKeyWord()
{
	if (!end)
		return;
	for (int i=0; KEY_WORD[i]; i++) {
		if (!strcmp(KEY_WORD[i], end->str)) {
			end->type = t_kword;
		}
	}
}

bool Lex::MachineWord(char c)
{
	if (state == fsm_start) {
		return 
			(c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z');
	} else if (state == fsm_word) {
		return 
			(c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') ||
			(c == '_');
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
		if (c == EOF)
			printf("ERR: MachineString: string literal isn't closed\n");
		return (c == '"');
	} else {
		printf("ERR: MachineOper: wrong state change\n");
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

bool Lex::MachineSep(char c)
{
	if (state == fsm_start) {
		return
			(c == '(') ||
			(c == ')') ||
			(c == '[') ||
			(c == ']') ||
			(c == '{') ||
			(c == '}') ||
			(c == ';') ||
			(c == ',');
	} else {
		printf("ERR: MachineAlgebra: wrong state change\n");
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
		case fsm_sep:
			t = t_sep;
			break;
	}
	Add(line, t);
	/*DEBUG*/ //printf("Pop:: poped\n");
	return true;
}

bool Lex::StepStart(char c)
{
	if (MachineWord(c)) {
		BufPut(c);
		state = fsm_word;
	} else if (MachineOper(c)) {
		BufPut(c);
		state = fsm_oper;
	} else if (MachineString(c)) {
		state = fsm_string;
	} else if (MachineNumber(c)) {
		BufPut(c);
		state = fsm_number;
	} else if (MachineAlgebra(c)) {
		BufPut(c);
		state = fsm_algebra;
	} else if (MachineSep(c)) {
		BufPut(c);
		state = fsm_sep;
	} else if (!IsSeparator(c) && (c != EOF)) {
		printf("\nERR: Step: wrong symbol at line %i [%c]\n\n",
			line_num, c);
		return false;
	}
	return true;
}

bool Lex::StepWord(char c)
{
	if (MachineWord(c)) {
		BufPut(c);
		return false;
	} else {
		Pop();
		CheckKeyWord();
		return true;
	}
}

bool Lex::StepOper(char c)
{
	if (MachineOper(c)) {
		BufPut(c);
		Pop();
		return false;
	} else {
		Pop();
		return true;
	}
}

bool Lex::StepString(char c)
{
	if (!MachineString(c)) {
		BufPut(c);
	} else {
		Pop();
		state = fsm_start;
	}
	return true;
}

bool Lex::StepNumber(char c)
{
	if (MachineNumber(c)) {
		BufPut(c);
		return false;
	} else {
		Pop();
		return true;
	}
}

/*
bool Lex::StepAlgebra(char c);
bool Lex::StepSep(char c);
*/

bool Lex::Step(char c)
{
	bool change = false;
	/*DEBUG*/ //printf("\n");
	/*DEBUG*/ //ShowState();
	/*DEBUG*/ //printf("[%c]\n", c);
	switch(state)
	{
		case fsm_start:
			if (!StepStart(c))
				return false;
			break;
		case fsm_word:
			change = StepWord(c);
			break;
		case fsm_oper:
			change = StepOper(c);
			break;
		case fsm_string:
			StepString(c);
			break;
		case fsm_number:
			change = StepNumber(c);
			break;
		case fsm_algebra:
		case fsm_sep:
			Pop(); change = true;
			break;
	}
	Separator(c);
	if (change) {
		state = fsm_start;
	}
	if (change && !IsSeparator(c)) {
		/*DEBUG*/ //printf("one more step");
		Step(c);
	} else if ((state != fsm_string) && IsSeparator(c)) {
		state = fsm_start;
	}
	return true;
	/*DEBUG*/ //ShowState();
	/*DEBUG*/ //printf("\n");
}

void Lex::ShowState()
{
	switch (state) {
		case fsm_start:
			printf("fsm_start\n");
			break;
		case fsm_word:
			printf("fsm_word\n");
			break;
		case fsm_oper:
			printf("fsm_oper\n");
			break;
		case fsm_string:
			printf("fsm_string\n");
			break;
		case fsm_number:
			printf("fsm_number\n");
			break;
		case fsm_algebra:
			printf("fsm_algebra\n");
			break;
		case fsm_sep:
			printf("fsm_sep\n");
			break;
	};
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
	printf("====================================\n");
	while((c = getc(file)) != EOF) {
		printf("%c", c);
		if (!Step(c)) {
			printf("ERR\n");
			return NULL;
		}
		//if (!BufPut(c)) //delete list
		//	return NULL;
	}
	if (!Step(c)) {
		printf("ERR\n");
		return NULL;
	}
	printf("====================================\n");
	/*DEBUG*/ //ListPrint();
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
					printf("t_kword  ");
					break;
				case t_word:
					printf("t_word   ");
					break;
				case t_oper:
					printf("t_oper   ");
					break;
				case t_string:
					printf("t_string ");
					break;
				case t_number:
					printf("t_number ");
					break;
				case t_algebra:
					printf("t_algebra");
					break;
				case t_sep:
					printf("t_sep    ");
					break;
			};
			printf("\t%i\t[%s]\n", t->line_num, t->str);
			t = t->next;
		}		
	}
}
