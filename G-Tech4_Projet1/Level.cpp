#include <iostream>
#include <stdio.h>
#include "Level.h"


Level::Level(int gridSizeX, int gridSizeY) : GridSizeX(gridSizeX), GridSizeY(gridSizeY)
{
}

Level::~Level()
{
}

void Level::intialize()
{

}

void Level::UpdateGrid()
{
	int x, y;

	for (y=0; y<GridSizeY; y++)
	{
		for (x=0; x<GridSizeX; x++)
		{
			std::cout << ".";
		}
		std::cout << std::endl;
	}
}
