#include "Game.h"
#include "Level.h"
#include "Input.h"
#include "Keyboard.h"

Game::Game()
{

}

Game::~Game()
{
}

void Game::Run()
{
	InputControl* inputControl = new Keyboard();

	Level Level1(10,10);

	Level1.InputUpdate(inputControl);
	Level1.UpdateGrid();
	
}



