#ifndef Level_hpp
#define Level_hpp

#include "Pawn.h"

class Level
{
public:

	Level(int gridSizeX, int gridSizeY);
	~Level();

	void intialize();
	void UpdateGrid();

protected:

	int GridSizeX;
	int GridSizeY;


};


#endif // !Level_hpp


#pragma once


