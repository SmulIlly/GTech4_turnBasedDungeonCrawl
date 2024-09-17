#include "Pawn.h"
#include "Player.h"


Pawn::Pawn()
{

}

Pawn::~Pawn()
{
}

Pawn* Pawn::Constructor(int id) {

	if (id == 1) {
		Player* newObj = new Player;
		return newObj;
	}
	else {
		return nullptr;
	}


}
