#ifndef LEVEL_H
#define LEVEL_H

#include "Tile.h"
#include "Pawn.h"
#include "Input.h"
#include "Monster.h"
#include <vector>

class Level
{
public:
    Pawn* player;
    std::vector<Pawn*> Monsters;
    std::vector<std::vector<Tile*>> grid;

    Level(int gridSizeX, int gridSizeY);
    ~Level();

    void initialize();
    void UpdateGrid();
    void InputUpdate();
    void endTurn();
    bool setRandomPosition(Pawn* pPawn);
    void move(Pawn* Pawn, int x, int y, int dis);
    void attack(Pawn* origin, Pawn* target);
    void ennemyTurn();

protected:
    int GridSizeX;
    int GridSizeY;

    int SelectorposX;
    int SelectorposY;
    bool inputFlag;
};

#endif // LEVEL_H