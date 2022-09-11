#ifndef GAMEMOD_H_SENTRY
#define GAMEMOD_H_SENTRY

class Game {
		struct list_player {
			class Player pl;
			class Player *next;
		};	
		struct list_player *list;
		//market info
		int level;
		int material;
		int material_price;
		int product;
		int product_price;
	public:
		Game();
		void SetMarket(int l, int m, int mp, int p, int pp);
		~Game();
};

#endif
