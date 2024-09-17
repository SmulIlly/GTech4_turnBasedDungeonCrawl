#ifndef Level_hpp
#define Level_hpp

#include "Pawn.h"
#include "Input.h"

class Level
{
public:

	Level(int gridSizeX, int gridSizeY, Pawn pawn);
	~Level();

	void intialize();
	void UpdateGrid();

	void InputUpdate(InputControl* inputDevice);

protected:

	int GridSizeX;
	int GridSizeY;
	Pawn AllPawn;

	bool inputFlag;

};


#endif // !Level_hpp


#pragma once


