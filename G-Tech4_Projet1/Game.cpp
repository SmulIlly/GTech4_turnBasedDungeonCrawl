#include "Game.h"
#include "Level.h"
#include "Input.h"
#include "Keyboard.h"

#include <string>;
#include <iostream>
#include <vector>

Game::Game()
{

}

Game::~Game()
{
}

void Game::Run()
{
	std::vector<std::string> map =
	{
		"-------------",
		"------@-S----",
		"-------------",
		"------------G",
		"-----------G-",
		"F---------G--",


	};

	int GridSizeY = map.size();
	int GridSizeX = map[0].length();

	srand(time(NULL));
	Level Level1(map, GridSizeX, GridSizeY);

	
	Level1.initialize();

	while (true) {
		Level1.InputUpdate();
		//Level1.UpdateGrid();
	}
	
}



