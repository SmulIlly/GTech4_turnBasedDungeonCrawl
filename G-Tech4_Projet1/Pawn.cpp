#include "Pawn.h"
#include "Player.h"
#include "Golem.h"
#include "Spectre.h"
#include "Faucheur.h"


Pawn::Pawn()
{

}

Pawn::~Pawn()
{
}

Pawn* Pawn::Constructor(int id) {

	if (id == 1) { //player
		Player* newObj = new Player;
		return newObj;
	}
	if (id == 2) { //golem
		Golem* newObj = new Golem;
		return newObj;
	}
	if (id == 3) { //spectre
		Spectre* newObj = new Spectre;
		return newObj;
	}
	if (id == 4) { //faucheur
		Faucheur* newObj = new Faucheur;
		return newObj;
	}
	else {
		return nullptr;
	}


}

bool Pawn::isGolem() { return false; }
bool Pawn::isSpectre() { return false; }
bool Pawn::isFaucheur() { return false; }
bool Pawn::isMonster() { return false; }
