#ifndef Pawn_hpp
#define Pawn_hpp



class Pawn
{
public:

	int posX;
	int posY;
	int maxMovement;
	int Movement;

	int HP;
	int Atk;

	bool m_dead = false;

	Pawn();
	~Pawn();

	static Pawn* Constructor(int id);
	virtual bool isGolem();
	virtual bool isSpectre();
	virtual bool isFaucheur();
	virtual bool isMonster();

private:

};

#endif // !Pawn_hpp

#pragma once



