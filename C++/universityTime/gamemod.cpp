#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gamemod.hpp"
#include "botmod.hpp"

Game::Game()
{
	list = NULL;
};

void Game::SetMarket(int l, int m, int mp, int p, int pp)
{
	level = l;
	material = m; material_price = mp;
	product = p; product_price = pp;
}

Game::~Game() {}; //TODO
