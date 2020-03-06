#ifndef BOTMOD_H_SENTRY
#define BOTMOD_H_SENTRY

#define INBUFSIZE 1024

class Player {
		int number;
		int money;
		int material;
		int product;
		int factory; 	
	public:
		void SetNum(int n);
		void SetMon(int m);
		void SetMat(int m);
		void SetProd(int p);
		void SetFac(int f);
		int GetNum();
		int GetMon();
		int GetMat();
		int GetProd();
		int GetFac();
};

class Bot: public Player {
		int sd;
		int buf_used;
		char buf[INBUFSIZE];
	public:
		Bot();
		bool BotConnect(char *address, char *str_port);
		void ShowSD();
		void ShowYourStats();
		void Say(const char *string);
		void UpdateStats();
		char *ListenStr();
		void ListenUntil(const char *string);
};


int is_it_sep(int c, const char *sep);
int word_count(const char *line, const char *sep);
void packline_print(char **packline);
int packline_size(char **packline);
void packline_free(const char **packline);
char **make_packline(const char *line, const char *sep);
#endif
