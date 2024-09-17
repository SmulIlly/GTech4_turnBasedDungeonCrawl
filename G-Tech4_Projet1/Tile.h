#ifndef TILE_H
#define TILE_H

#include "Pawn.h"

class Tile
{
public:
    Pawn* pPawn;
    bool isWalkable;

    Tile();
    ~Tile();
};

#endif // TILE_H