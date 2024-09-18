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

    //monster spawn
    Monsters.push_back(Pawn::Constructor(2));
    Monsters.push_back(Pawn::Constructor(3));
    Monsters.push_back(Pawn::Constructor(4));
    for (int x = 0; x < Monsters.size(); x++) {
        setRandomPosition(Monsters[x]);
    }


    UpdateGrid();
}

void Level::UpdateGrid()
{
    //Monsters in grid
    for (auto i = Monsters.begin(); i != Monsters.end();) {
        if ((*i)->m_dead == false)
        {
            grid[(*i)->posX][(*i)->posY]->pPawn = *i;
            ++i; // Avancer l'itérateur si l'élément n'est pas supprimé
        }
        else
        {
            i = Monsters.erase(i); // Supprimer l'élément et obtenir l'itérateur suivant
        }
    }

    //Player in grid
    grid[player->posX][player->posY]->pPawn = player;
    for (int y = 0; y < GridSizeY; ++y)
    {
        for (int x = 0; x < GridSizeX; ++x)
        {
            int disX = std::abs(x - player->posX);
            int disY = std::abs(y - player->posY);
            int dis = disX + disY;

            grid[x][y]->isWalkable = false;
            grid[x][y]->isAttackable = false;
            if (dis > 0 && dis <= player->Movement && grid[x][y]->pPawn == nullptr) {
                grid[x][y]->isWalkable = true;
            }
            if (dis <= player->Movement + 1 && grid[x][y]->pPawn != nullptr) {
                if (grid[x][y]->pPawn->isMonster() == true && grid[x][y]->pPawn->m_dead == false) {
                    grid[x][y]->isAttackable = true;
                }
                
            }

        }
    }


    //check dead
    for (int y = 0; y < GridSizeY; ++y)
    {
        for (int x = 0; x < GridSizeX; ++x)
        {
            if (grid[x][y]->pPawn != nullptr && grid[x][y]->pPawn->m_dead == true) {
                grid[x][y]->pPawn = nullptr;

            }
        }
    }

    // Affichage
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k;


    if (grid[SelectorposX][SelectorposY]->pPawn != nullptr) // HUD des stat du monstre selectioner
    {
        if (grid[SelectorposX][SelectorposY]->pPawn->isMonster() == true)
        {
            Pawn* EnemySelected = grid[SelectorposX][SelectorposY]->pPawn;
            std::cout<< grid[SelectorposX][SelectorposY]->pPawn->name << " :" << "   HP : " << grid[SelectorposX][SelectorposY]->pPawn->HP << "   ATK : " << grid[SelectorposX][SelectorposY]->pPawn->Atk << std::endl << std::endl;
        }
        else
        {
            std::cout << std::endl << std::endl;
        }
    }
    else
    {
        std::cout << std::endl << std::endl;
    }



    for (int y = 0; y < GridSizeY; ++y)
    {
        for (int x = 0; x < GridSizeX; ++x)
        {
            k = 15;
            if (grid[x][y]->isWalkable == true) {
                k = 23;
            }
            if (grid[x][y]->isAttackable == true) {
                k = 215;
            }
            if (y == SelectorposY && x == SelectorposX) {
                k = 71; // Couleur ou attribut pour le sélecteur
            }

            SetConsoleTextAttribute(hConsole, k);

            if (grid[x][y]->pPawn == nullptr) {
                std::cout << "[ ]";
            }
            else {
                if (grid[x][y]->pPawn == player) {
                    std::cout << "[@]";
                }
                if (grid[x][y]->pPawn->isGolem() == true) {
                    std::cout << "[G]";
                }
                if (grid[x][y]->pPawn->isSpectre() == true) {
                    std::cout << "[S]";
                }
                if (grid[x][y]->pPawn->isFaucheur() == true) {
                    std::cout << "[F]";
                } 
            }
        }
        k = 15;
        SetConsoleTextAttribute(hConsole, k);
        std::cout << std::endl;
    }

    std::cout  // affichage des stat du joueur
        << " " << player->name << " :" << std::endl
        << "  - HP  = " << player->HP << std::endl
        << "  - ATK = " << player->Atk;
}

void Level::InputUpdate()
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
            if (grid[SelectorposX][SelectorposY]->pPawn == nullptr) { //if position is not the same as player or monster
                Level::move(player, SelectorposX, SelectorposY, dis);
            }
            UpdateGrid();
        }
        if (dis == 1) {
            if (grid[SelectorposX][SelectorposY]->pPawn != nullptr) {
                if (grid[SelectorposX][SelectorposY]->pPawn->isMonster() == true) {
                    Level::attack(player, grid[SelectorposX][SelectorposY]->pPawn);
                }
            }
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

bool Level::setRandomPosition(Pawn* pPawn) {

    int x = rand() % GridSizeX;
    int y = rand() % GridSizeY;
    if (x != player->posX || y != player->posY) { //if position is not the same as player
        for (int i = 0; i < Monsters.size(); i++) {
            if (x != Monsters[i]->posX || y != Monsters[i]->posY) { //and its not the same as any monsters
                pPawn->posX = x;
                pPawn->posY = y;
                return true;
            }
        }

    }
    else {
        setRandomPosition(pPawn);
    }
}

void Level::move(Pawn* pawn, int x, int y, int dis) {
    
     pawn->Movement -= dis;
     grid[pawn->posX][pawn->posY]->pPawn = nullptr;
     pawn->posX = x;
     pawn->posY = y;
     grid[player->posX][player->posY]->pPawn = player;
}

void Level::attack(Pawn* origin, Pawn* target) {
    target->HP -= origin->Atk;
    if (target->HP <= 0) {
        target->m_dead = true;
    }
    endTurn();
}