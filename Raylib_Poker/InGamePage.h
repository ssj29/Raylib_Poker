#pragma once
#include"InitGame.h"

class InGamePage : public InitGame
{
private:

public:
	/*Table tableObj;*/
	Player _plyer1;
	Player _plyer2;
	InGamePage();
	void SetInGamePage();
	void UpdateInGamePage(Table&,Player&,Player&);
	//std::vector<Player> _players;

};