#include "Input.h"

class Keyboard : public InputControl
{
public:
	//bool isQWERTY();
	//bool isAZERTY();


	bool isUPpressed();
	bool isDOWNpressed();
	bool isLEFTpressed();
	bool isRIGHTpressed();



	void updateInput() override;

};