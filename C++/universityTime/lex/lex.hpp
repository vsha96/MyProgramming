#include <stdio.h>
#ifndef LEX_H_SENTRY
#define LEX_H_SENTRY

#ifndef LEX_STR_LIMIT
#define LEX_STR_LIMIT 128
#endif

enum Type {
	t_kword,
	t_word,
	t_oper,
	t_string,
	t_number,
	t_algebra,
	t_sep
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
			fsm_algebra,
			fsm_sep
		};
		
		char buf[LEX_STR_LIMIT];
		int buf_used;

		FILE *file;
		State state;
		int line_num;
		List *list; //this must be returned by Analyze
		List *end;
		
		bool BufPut(char c);
		bool IsSeparator(char c);
		bool Separator(char c);
		void CheckKeyWord();
		bool MachineWord(char c);
		bool MachineOper(char c);
		bool MachineString(char c);
		bool MachineNumber(char c);
		bool MachineAlgebra(char c);
		bool MachineSep(char c);
		void Add(const char *str, Type type);
		bool Pop();
		bool StepStart(char c);
		bool StepWord(char c);
		bool StepOper(char c);
		bool StepString(char c);
		bool StepNumber(char c);
		//bool StepAlgebra(char c);
		//bool StepSep(char c);
		bool Step(char c);
		void ShowState();
	public:
		Lex();
		List *Analyze(char *file);
		void ListPrint();
};

#endif
