#include "Game.h"
#include "Level.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Run()
{
	Level Level1(10,10);

	Level1.UpdateGrid();
}



