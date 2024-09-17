#ifndef Level_hpp
#define Level_hpp

#include "Pawn.h"

class Level
{
public:

	Level(int gridSizeX, int gridSizeY, Pawn pawn);
	~Level();

	void intialize();
	void UpdateGrid();

protected:

	int GridSizeX;
	int GridSizeY;
	Pawn AllPawn;

};


#endif // !Level_hpp


#pragma once


