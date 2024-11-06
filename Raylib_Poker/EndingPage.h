#pragma once
#include"InitGame.h"

class EndingPage : public InitGame
{
private:

public:
	EndingPage();

	void SetEndingPage(Table&,Player&,Player&);
	~EndingPage();
};