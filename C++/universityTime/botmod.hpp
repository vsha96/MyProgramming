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

struct Market {
	int level;
	int material;
	int material_price;
	int product;
	int product_price;
};

class Game {
    struct list_player {
        class Player pl; 
        struct list_player *next;
    };
	enum GameState {
		game_playing,
		game_end
	};
		int turn;
		GameState state;
		list_player *list;
		Market market;
    public:
        Game();
		void AddPlayer(int num, int mon, int mat, int prod, int fac);
		void SetPlayer(int num, int mon, int mat, int prod, int fac);
		void ShowPlayer();
        void SetMarket(int l, int m, int mp, int p, int pp);
		void ShowMarket();
		Market GetMarket();
		void Turn();
		void End();
		//int GetMarket ...
        ~Game();
};

class Bot: public Player {
	enum State {
		bot_playing,
		bot_winner,
		bot_loser
	};
		int sd;
		int buf_used;
		char buf[INBUFSIZE];
		Game *game;
		State state;
	public:
		Bot(Game *g);
		bool BotConnect(char *address, char *str_port);
		void ShowSD();
		void ShowStats();
		void ShowMarket();
		void Say(const char *string);
		void UpdateStats();
		void UpdateMarket();
		void SetPlayer(int num, int mon, int mat, int prod, int fac);
		void ShowPlayer();
		void UpdatePlayer();
		char *ListenStr();
		void ListenUntil(const char *string);
		void ListenUntilPart(const char *string);
		void Produce(int count);
		void Buy(int count, int price);
		void Sell(int count, int price);
		void Build(int count);
		bool EndTurn();
		~Bot(); //TODO maybe it's not necessary
};

#endif
