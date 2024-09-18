#include "Game.h"
#include "Level.h"
#include "Input.h"
#include "Keyboard.h"

#include <string>;
#include <iostream>
#include <vector>
#include <fstream>

Game::Game()
{

}

Game::~Game()
{
}

void Game::Run()
{
	std::vector<std::string> map;
	std::string Line;
	std::ifstream MapText("C:/Users/bdaniel/Documents/GitHub/GTech4_turnBasedDungeonCrawl/Map/Map1.txt");

	if(MapText)
	{
		while (getline(MapText,Line))
		{
			map.push_back(Line);
		}
	}
	else
	{
		std::cout << "je ne trouve pas le fichier text de la map";
	}

	/*{
		"---G-----G--",
		"---G--@-G---",
		"GGG----GG---",
		"----G-------",
		"GG-G-----GGG",
		"---G----G---",


	};*/

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



