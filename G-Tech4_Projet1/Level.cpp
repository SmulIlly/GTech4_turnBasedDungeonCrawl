#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <queue>
#include "Level.h"

// Définition des codes des touches
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define SPACE 32
#define ESC 27

Level::Level(const std::vector<std::string>& map, int gridSizeX, int gridSizeY)
    :map(map), GridSizeX(gridSizeX), GridSizeY(gridSizeY), player(Pawn::Constructor(1)), SelectorposX(0), SelectorposY(0), inputFlag(false)
{}

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

    //default player values if no player in map
    player->posX = GridSizeX/2;
    player->posY = GridSizeY/2;
    player->maxMovement = 3;
    player->Movement = player->maxMovement;
    player->HP = 3;
    player->m_dead = false;


    for (int y = 0; y < GridSizeY; y++) {
        for (int x = 0; x < GridSizeX; x++) {
            char c = map[y].at(x);
            if (c == '@') {
                player->posX = x;
                player->posY = y;
            }
        }
    }
    SelectorposX = player->posX;
    SelectorposY = player->posY;
    grid[player->posX][player->posY]->pPawn = player;


    //monster spawn
    for (int y = 0; y < GridSizeY; y++) {
        for (int x = 0; x < GridSizeX; x++) {
            char c = map[y].at(x);
            if (c == 'G') {
                Pawn* newGolem = Pawn::Constructor(2);
                newGolem->posX = x;
                newGolem->posY = y;
                Monsters.push_back(newGolem);
            }
            if (c == 'S') {
                Pawn* newSpectre = Pawn::Constructor(3);
                newSpectre->posX = x;
                newSpectre->posY = y;
                Monsters.push_back(newSpectre);
            }
            if (c == 'F') {
                Pawn* newFaucheur = Pawn::Constructor(4);
                newFaucheur->posX = x;
                newFaucheur->posY = y;
                Monsters.push_back(newFaucheur);
            }
        }
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


    calculateWalkableAndAttackable();


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
    if (player->m_dead == true) {
        GameOver();
    }

    // Affichage
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int k;
    std::string ActionType("Move");

    if (grid[SelectorposX][SelectorposY]->pPawn != nullptr) // HUD des stat du monstre selectioner
    {
        if (grid[SelectorposX][SelectorposY]->pPawn->isMonster() == true)
        {
            ActionType = "Attack";
            Pawn* EnemySelected = grid[SelectorposX][SelectorposY]->pPawn;
            std::cout<< grid[SelectorposX][SelectorposY]->pPawn->name << " :" << "   HP : " << grid[SelectorposX][SelectorposY]->pPawn->HP << "   ATK : " << grid[SelectorposX][SelectorposY]->pPawn->Atk << std::endl << std::endl;
        }
        else
        {
            std::cout << grid[SelectorposX][SelectorposY]->pPawn->name << std::endl << std::endl;
        }
    }
    else
    {
        std::cout << "Empty" << std::endl << std::endl;
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
        << " " << player->name << " :" << "                 Controlle :" << std::endl
        << "  - HP  = " << player->HP  << "                       [SPACE]:  " << ActionType << std::endl
        << "  - ATK = " << player->Atk << "                       [ESCAPE]: Pass Turn";
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
            if (grid[SelectorposX][SelectorposY]->isWalkable == true) {
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
    ennemyTurn();
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

void Level::calculateWalkableAndAttackable() {


    for (int y = 0; y < GridSizeY; ++y) {
        for (int x = 0; x < GridSizeX; ++x) {
            grid[x][y]->isWalkable = false;
            grid[x][y]->isAttackable = false;
        }
    }

    int directionX[] = { 0, 0, -1, 1 };
    int directionY[] = { -1, 1, 0, 0 };
    std::queue<std::pair<int, int>> bfsQueue;
    std::vector<std::vector<int>> distance(GridSizeX, std::vector<int>(GridSizeY, -1));

    // Start BFS from player's position
    bfsQueue.push({ player->posX, player->posY });
    distance[player->posX][player->posY] = 0;
    grid[player->posX][player->posY]->isWalkable = false;

    while (!bfsQueue.empty()) {
        std::pair<int, int> currentPos = bfsQueue.front(); // Explicitly declare the type
        int currentX = currentPos.first;
        int currentY = currentPos.second;
        bfsQueue.pop();

        int currentDistance = distance[currentX][currentY];

        // If we are at the maximum movement distance, stop expanding
        if (currentDistance >= player->Movement) continue;

        // Check all 4 adjacent directions (up, down, left, right)
        for (int i = 0; i < 4; ++i) {
            int nextX = currentX + directionX[i];
            int nextY = currentY + directionY[i];

            // Check if the next position is within bounds
            if (nextX >= 0 && nextX < GridSizeX && nextY >= 0 && nextY < GridSizeY) {
                // If the cell hasn't been visited yet and is empty, continue BFS
                if (distance[nextX][nextY] == -1 && grid[nextX][nextY]->pPawn == nullptr) {
                    distance[nextX][nextY] = currentDistance + 1;
                    grid[nextX][nextY]->isWalkable = true;
                    bfsQueue.push({ nextX, nextY });
                }

                // Mark adjacent monsters as attackable if within the attack range
                if (grid[nextX][nextY]->pPawn != nullptr && grid[nextX][nextY]->pPawn->isMonster() && !grid[nextX][nextY]->pPawn->m_dead) {
                    grid[nextX][nextY]->isAttackable = true;
                }
            }
        }
    }
}

void Level::move(Pawn* pawn, int x, int y, int dis) {
    
     pawn->Movement -= dis;
     grid[pawn->posX][pawn->posY]->pPawn = nullptr;
     pawn->posX = x;
     pawn->posY = y;
     grid[pawn->posX][pawn->posY]->pPawn = pawn;
}

void Level::attack(Pawn* origin, Pawn* target) {
    if (target->isGolem() == false) {
        target->HP -= origin->Atk;
        //log attack
        Log(origin->name + " attacked " + target->name + " for " + std::to_string(origin->Atk) + " damage!");
    }
    else {
        int save = rand() % 2;
        if (save == 0) {
            target->HP -= origin->Atk;
            //log attack
            Log(origin->name + " attacked " + target->name + " for " + std::to_string(origin->Atk) + " damage!");
        }
        else {
            //log save
            Log(origin->name + " attacked " + target->name + " but Golem blocked it");
        }
    }

    origin->Movement = 0;
    if (target->HP <= 0) {
        target->m_dead = true;
        if (target->isGolem() == true) { //golem was killed
            player->Atk++;
        }
        if (target->isSpectre() == true) { //Spectre was killed
            player->HP = 3;
        }
        if (target->isFaucheur() == true) { //Faucheur was killed
            for (int i = 0; i < Monsters.size(); i++) {
                Monsters[i]->HP -= 2;
            }
        }
        //log killed
        Log(target->name + " got killed");
    }

    if (origin == player) {
        endTurn();
    }
    
}

void Level::ennemyTurn() {
    for (int i = 0; i < Monsters.size(); i++) {
        Monsters[i]->Movement = Monsters[i]->maxMovement;
        int disX = std::abs(Monsters[i]->posX - player->posX);
        int disY = std::abs(Monsters[i]->posY - player->posY);
        int dis = disX + disY;
        if (dis == 1) {
            Level::attack(Monsters[i], player);
        }

        //Monster specific behaviour
        if (Monsters[i]->isFaucheur() == true) {
            //avancer vers joueur
            for (Monsters[i]->Movement; Monsters[i]->Movement > 0; /*Monsters[i]->Movement--*/) {
                if (dis > 1) {
                    if (disX >= disY) {
                        if (Monsters[i]->posX > player->posX) {
                            int newpos = Monsters[i]->posX -1;
                            move(Monsters[i], newpos, Monsters[i]->posY, 1);
                         
                        }
                        if (Monsters[i]->posX < player->posX) {
                            int newpos = Monsters[i]->posX + 1;
                            move(Monsters[i], newpos, Monsters[i]->posY, 1);
                         
                        }
                    }
                    else {
                        if (Monsters[i]->posY > player->posY) {
                            int newpos = Monsters[i]->posY - 1;
                            move(Monsters[i], Monsters[i]->posX, newpos, 1);
                        
                        }
                        if (Monsters[i]->posY < player->posY) {
                            int newpos = Monsters[i]->posY + 1;
                            move(Monsters[i], Monsters[i]->posX, newpos, 1);
                            
                        }
                    }
                }
            }
        }
        if (Monsters[i]->isSpectre() == true) {
            //s'enfuir du joueur
            
            for (Monsters[i]->Movement; Monsters[i]->Movement > 0; Monsters[i]->Movement--) {
                if (dis > 1) {
                    if (disX >= disY) {
                        if (Monsters[i]->posX < GridSizeX-1 && Monsters[i]->posX >0) {
                            if (Monsters[i]->posX > player->posX) {
                                int newpos = Monsters[i]->posX + 1;
                                move(Monsters[i], newpos, Monsters[i]->posY, 1);
                            }
                            if (Monsters[i]->posX < player->posX) {
                                int newpos = Monsters[i]->posX - 1;
                                move(Monsters[i], newpos, Monsters[i]->posY, 1);
                            }
                        }
                    }
                    else {
                        if (Monsters[i]->posY < GridSizeY-1 && Monsters[i]->posY >0) {
                            if (Monsters[i]->posY > player->posY) {
                                int newpos = Monsters[i]->posY + 1;
                                move(Monsters[i], Monsters[i]->posX, newpos, 1);
                                
                            }
                            if (Monsters[i]->posY < player->posY) {
                                int newpos = Monsters[i]->posY - 1;
                                move(Monsters[i], Monsters[i]->posX, newpos, 1);
                            }
                        }
                    }

                }
                
               
            }
        }

    }
}

void Level::Log(std::string log) {
    Logs.push_back(log);
}

void Level::GameOver() {
    Reset();
}

void Level::Reset() {
    for (auto& monster : Monsters) {
        delete monster;
    }
    Monsters.clear();

    for (auto& row : grid) {
        for (auto& tile : row) {
            delete tile;
        }
    }
    grid.clear();

    Logs.clear();

    initialize();
}