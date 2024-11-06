#include"WelcomePage.h"

WelcomePage::WelcomePage()
{
	//WelcomePage::SetWelcomePage();
}

WelcomePage::~WelcomePage()
{

}

void WelcomePage::SetWelcomePage()
{
	BeginDrawing();
	SetTargetFPS(60);
	ClearBackground(DARKBLUE);
	DrawText(" Poker ", 425, 250, 80, RAYWHITE);
	DrawText(" Press enter or Click", 400, 350, 30, RAYWHITE);
	EndDrawing();
}