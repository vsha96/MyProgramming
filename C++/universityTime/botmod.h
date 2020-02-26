#ifndef BOTMOD_H_SENTRY
#define BOTMOD_H_SENTRY

#define INBUFSIZE 128

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
};

class Bot: public Player {
		int sd;
		char buf[INBUFSIZE];
	public:
		Bot();
		bool BotConnect(char *address, char *str_port);
		void ShowSD();
		void Say(char *string);
		char *ListenStr();
		void ListenUntill(char *string);
};
#endif
