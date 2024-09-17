#ifndef TILE_H
#define TILE_H

#include "Pawn.h"

class Tile
{
public:
    Pawn* pPawn;
    bool isWalkable;
    bool isAttackable;

    Tile();
    ~Tile();
};

#endif // TILE_H