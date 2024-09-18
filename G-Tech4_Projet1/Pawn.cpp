#include "Pawn.h"
#include "Player.h"
#include "Golem.h"
#include "Spectre.h"
#include "Faucheur.h"


Pawn::Pawn() : HP(0), Atk(0), maxMovement(0), Movement(0), posX(0), posY(0), name("")
{

}

Pawn::~Pawn()
{
}

Pawn* Pawn::Constructor(int id) {

	if (id == 1) { //player
		Player* newObj = new Player;
		newObj->HP = 3;
		newObj->Atk = 1;
		newObj->name = "Player";
		return newObj;
	}
	if (id == 2) { //golem
		Golem* newObj = new Golem;
		newObj->maxMovement = 0;
		newObj->HP = 2;
		newObj->Atk = 2;
		newObj->name = "Golem";
		return newObj;
	}
	if (id == 3) { //spectre
		Spectre* newObj = new Spectre;
		newObj->maxMovement = 1;
		newObj->HP = 1;
		newObj->Atk = 1;
		newObj->name = "Spectre";
		return newObj;
	}
	if (id == 4) { //faucheur
		Faucheur* newObj = new Faucheur;
		newObj->maxMovement = 1;
		newObj->HP = 5;
		newObj->Atk = 3;
		newObj->name = "Faucheur";
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
