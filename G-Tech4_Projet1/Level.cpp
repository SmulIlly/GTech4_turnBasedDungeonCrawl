#include "Level.h"


Level::Level(int gridSizeX, int gridSizeY, Pawn pawn) : GridSizeX(gridSizeX), GridSizeY(gridSizeY), AllPawn(pawn)
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
