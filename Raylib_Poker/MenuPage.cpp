#include"MenuPage.h"

MenuPage::MenuPage()
{
	MenuPage::SetMenuPage();
}

void MenuPage::SetMenuPage()
{
	BeginDrawing();
	ClearBackground(DARKBLUE);
	//DrawCircle(530, 350, 350, RED);
	DrawText(" MENU ", 450, 200, 60, RAYWHITE);
	DrawText(" Press 1 or 2 or 3 ", 300, 300, 30, RAYWHITE);
	DrawText(" 1) Start Game", 300, 350, 30, RAYWHITE);
	DrawText(" 2) Game History", 300, 400, 30, RAYWHITE);
	DrawText(" 3) Exit Game", 300, 450, 30, RAYWHITE);
	DrawText(" Press Backspace to go back page", 300, 550, 25, RAYWHITE);
	EndDrawing();
}