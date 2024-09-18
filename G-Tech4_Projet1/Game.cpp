#include "Game.h"
#include "Level.h"
#include "Input.h"
#include "Keyboard.h"

#include <string>;
#include <iostream>

Game::Game()
{

}

Game::~Game()
{
}

void Game::Run()
{
	std::string map[] =
	{
		"----------",
		"----------",
		"----------",
		"----------",
		"----------",
	};


	srand(time(NULL));
	Level Level1(20,10);

	
	Level1.initialize();

	while (true) {
		Level1.InputUpdate();
		//Level1.UpdateGrid();
	}
	
}



