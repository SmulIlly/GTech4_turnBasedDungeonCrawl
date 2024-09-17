#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include "Level.h"

// Définition des codes des touches
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define SPACE 32
#define ESC 27

Level::Level(int gridSizeX, int gridSizeY)
    : GridSizeX(gridSizeX), GridSizeY(gridSizeY), player(Pawn::Constructor(1)), SelectorposX(0), SelectorposY(0), inputFlag(false)
{
}

Level::~Level()
{
    for (auto& row : grid) {
        for (auto& tile : row) {
            delete tile;
        }
    }
}

void Level::initialize()
{
    std::vector<Tile*> line;

    for (int i = 0; i < GridSizeX; ++i) {
        for (int y = 0; y < GridSizeY; ++y) {
            Tile* newTile = new Tile;
            newTile->pPawn = nullptr;
            newTile->isWalkable = false;
            line.push_back(newTile);
        }
        grid.push_back(line);
        line.clear();
    }

    player->posX = 1;
    player->posY = 3;
    player->maxMovement = 5;
    player->Movement = player->maxMovement;
    SelectorposX = player->posX;
    SelectorposY = player->posY;
    grid[player->posX][player->posY]->pPawn = player;

    UpdateGrid();
}

void Level::UpdateGrid()
{
    grid[player->posX][player->posY]->pPawn = player;
    for (int y = 0; y < GridSizeY; ++y)
    {
        for (int x = 0; x < GridSizeX; ++x)
        {
            int disX = std::abs(x - player->posX);
            int disY = std::abs(y - player->posY);
            int dis = disX + disY;
            if (dis > 0 && dis < player->Movement + 1) {
                grid[x][y]->isWalkable = true;
            }
            else {
                grid[x][y]->isWalkable = false;
            }
        }
    }

    // Affichage
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k;

    for (int y = 0; y < GridSizeY; ++y)
    {
        for (int x = 0; x < GridSizeX; ++x)
        {
            k = 15;
            if (grid[x][y]->isWalkable == true) {
                k = 23;
            }
            if (y == SelectorposY && x == SelectorposX) {
                k = 71; // Couleur ou attribut pour le sélecteur
            }

            SetConsoleTextAttribute(hConsole, k);

            if (grid[x][y]->pPawn == nullptr) {
                std::cout << "[ ]";
            }
            if (grid[x][y]->pPawn == player) {
                std::cout << "[@]";
            }
        }
        k = 15;
        SetConsoleTextAttribute(hConsole, k);
        std::cout << std::endl;
    }
}

void Level::InputUpdate(InputControl* inputDevice)
{
    int pressedKey = _getch();
    //std::cout << pressedKey;

    if (pressedKey == UP) {
        if (SelectorposY > 0) {
            SelectorposY -= 1;
            UpdateGrid();
        }
    }
    if (pressedKey == DOWN) {
        if (SelectorposY < GridSizeY - 1) {
            SelectorposY += 1;
            UpdateGrid();
        }
    }
    if (pressedKey == RIGHT) {
        if (SelectorposX < GridSizeX - 1) {
            SelectorposX += 1;
            UpdateGrid();
        }
    }
    if (pressedKey == LEFT) {
        if (SelectorposX > 0) {
            SelectorposX -= 1;
            UpdateGrid();
        }
    }
    if (pressedKey == SPACE) {
        int disX = std::abs(SelectorposX - player->posX);
        int disY = std::abs(SelectorposY - player->posY);
        int dis = disX + disY;
        if (dis <= player->Movement) {
            player->Movement -= dis;
            grid[player->posX][player->posY]->pPawn = nullptr;
            player->posX = SelectorposX;
            player->posY = SelectorposY;
            grid[player->posX][player->posY]->pPawn = player;
            UpdateGrid();
        }
    }
    if (pressedKey == ESC) {
        endTurn();
    }
}

void Level::endTurn() {
    // ENNEMY TURN //
    player->Movement = player->maxMovement;
    UpdateGrid();
}