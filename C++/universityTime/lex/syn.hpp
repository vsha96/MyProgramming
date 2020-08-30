#include "lex.hpp"
#ifndef SYN_H_SENTRY
#define SYN_H_SENTRY
	
class ErrLex { //this will be thrown
		List *err_lex;
		int err_code;
		const char* err_msg;
	public:
		ErrLex(List *err_lex, int err_code, const char* err_msg);
		ErrLex(const ErrLex &other);
		~ErrLex();
		void GetMsg();
};

class Syn {
		List *cl; //current lexeme
	public:
		Syn();
		void CheckGrammar(List *first);
	private:
		bool go();
};

#endif
