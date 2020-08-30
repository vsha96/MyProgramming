#include "lex.hpp"
#include "syn.hpp"

ErrLex::ErrLex(List *lex, int code, const char* msg)
{
	err_lex = lex;
	err_code = code;
	err_msg = msg;
}

ErrLex::ErrLex(const ErrLex &other)
{
	//TODO	
}

ErrLex::~ErrLex()
{
	//TODO
}

Syn::Syn()
{
	cl = NULL;
}

void Syn::CheckGrammar(List *first)
{
	cl = first;
}

bool Syn::go()
{
	if (cl) {
		cl = cl->next;
	} else {
		printf("WARN: Syn::go: &current_lex = NULL\n");
		return false;
	}
	return true;
}




