#ifndef LEVEL_H
#define LEVEL_H

#include "Tile.h"
#include "Pawn.h"
#include "Input.h"
#include "Monster.h"
#include <vector>
#include <string>

class Level
{
public:
    Pawn* player;
    std::vector<Pawn*> Monsters;
    std::vector<std::vector<Tile*>> grid;
    std::vector<std::string> Logs;


    Level(const std::vector<std::string>& map, int gridSizeX, int gridSizeY);
    ~Level();

    void initialize();
    void UpdateGrid();
    void InputUpdate();
    void endTurn();
    bool setRandomPosition(Pawn* pPawn);
    void move(Pawn* Pawn, int x, int y, int dis);
    void attack(Pawn* origin, Pawn* target);
    void ennemyTurn();
    void Log(std::string log);
    void GameOver();
    void Reset();

protected:
    std::vector<std::string> map;
    int GridSizeX;
    int GridSizeY;

    int SelectorposX;
    int SelectorposY;
    bool inputFlag;
};

#endif // LEVEL_H