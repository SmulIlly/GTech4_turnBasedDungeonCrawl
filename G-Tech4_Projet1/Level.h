#ifndef LEVEL_H
#define LEVEL_H

#include "Tile.h"
#include "Pawn.h"
#include "Input.h"
#include <vector>

class Level
{
public:
    Pawn* player;
    std::vector<std::vector<Tile*>> grid;

    Level(int gridSizeX, int gridSizeY);
    ~Level();

    void initialize();
    void UpdateGrid();
    void InputUpdate(InputControl* inputDevice);
    void endTurn();

protected:
    int GridSizeX;
    int GridSizeY;

    int SelectorposX;
    int SelectorposY;
    bool inputFlag;
};

#endif // LEVEL_H