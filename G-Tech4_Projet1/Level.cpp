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

void Level::InputUpdate(InputControl* inputDevice) {

    /*          Inputs          */

    inputDevice->updateInput();


    if (inputDevice->m_state & InputControl::UP) {
        if (inputFlag == false) {
            //put logic here
        }


        inputFlag = true;
    }

    if (inputDevice->m_state & InputControl::DOWN) {
        if (inputFlag == false) {
            //put logic here
        }


        inputFlag = true;
    }

    if (inputDevice->m_state & InputControl::LEFT) {
        if (inputFlag == false) {
            //put logic here
        }


        inputFlag = true;
    }

    if (inputDevice->m_state & InputControl::RIGHT) {
        if (inputFlag == false) {
            //put logic here
        }


        inputFlag = true;
    }


    if (inputDevice->m_state & InputControl::SPACE) {
        if (inputFlag == false) {
            //put logic here
        }


        inputFlag = true;
    }
    if (inputDevice->m_state & InputControl::ESC) {
        if (inputFlag == false) {
            //put logic here
        }


        inputFlag = true;
    }
    else {
        inputFlag = false;
    }


    /*     End Of Input     */


}
