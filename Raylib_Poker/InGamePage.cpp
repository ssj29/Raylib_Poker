
#include"InGamePage.h"
#include"pokernew/MainMenu.h"


InGamePage::InGamePage()
{
}

void InGamePage::SetInGamePage()
{
	BeginDrawing();
	ClearBackground(RAYWHITE);
	DrawCircle(530, 350, 350, RED);
	DrawText(" In-Game ", 430, 200, 40, BLACK);
	DrawText("Game starts now ", 360, 250, 40, BLACK);
	EndDrawing();
}

void InGamePage::UpdateInGamePage(Table &_tableObj, Player &_player1Obj, Player &_player2Obj)
{	
	InitGame::_tableObj->GamePlay(_tableObj, _player1Obj, _player2Obj);

	std::string _playerName = _player1Obj.GetName();
	std::string _playerMoney = std::to_string(_player1Obj.GetMoney());

	std::string _AIName = _player2Obj.GetName();
	std::string _AIMoney = std::to_string(_player2Obj.GetMoney());

	std::string _potMoney = std::to_string(_tableObj.GetMoney());

	std::vector<std::string> _tableCards = _tableObj.GetHiddenCards();

	int tableCardsCount = 2;
	int tableCardsSpace_X = 250;
	int playerCardsSpace_X = 100;
	int player2CardsSpace_X = 700;

	BeginDrawing();
	ClearBackground(DARKGREEN);
	DrawText(" Table Setup ", 400, 50, 40, BLACK);
	DrawText(" 20 Rs from both player added  to round", 350, 100, 20, BLACK);

	DrawText(" POT Money: ", 500, 130, 20, BLACK);
	DrawText(_potMoney.c_str(), 550, 150, 20, BLACK);

	DrawText(" Table Cards Below", 450, 190, 20, BLACK);

	std::string cardPath;
	for (int i = 0; i < _tableObj.call; i++)
	{
		cardPath = "Cards/" + _tableCards.at(i) + ".png";
		Image card = LoadImage(cardPath.c_str());
		ImageResize(&card, 70, 100);
		Texture2D texture = LoadTextureFromImage(card);
		DrawTexture(texture, tableCardsSpace_X, 240, WHITE);
		tableCardsSpace_X += 120;
	}

	for (int i = 0; i < _player1Obj.playerHand.size(); i++)
	{
		cardPath = "Cards/" + _player1Obj.playerHand.at(i) + ".png";
		Image card = LoadImage(cardPath.c_str());
		ImageResize(&card, 70, 100);
		Texture2D texture = LoadTextureFromImage(card);
		DrawTexture(texture, playerCardsSpace_X, 380, WHITE);
		playerCardsSpace_X += 120;
	}
	DrawText(" Player Name: ", 100, 500, 20, BLACK);
	DrawText(_playerName.c_str(), 250, 500, 20, BLACK);
	DrawText(" Player Money: ", 100, 550, 20, BLACK);
	DrawText(_playerMoney.c_str() , 280, 550, 20, BLACK);


	for (int i = 0; i < _player2Obj.playerHand.size(); i++)
	{
		cardPath = "Cards/Card_Back.png";
		Image card = LoadImage(cardPath.c_str());
		ImageResize(&card, 70, 100);
		Texture2D texture = LoadTextureFromImage(card);
		DrawTexture(texture, player2CardsSpace_X, 380, WHITE);
		player2CardsSpace_X += 120;
	}
	DrawText(" AI Name: ", 700, 500, 20, BLACK);
	DrawText(_AIName.c_str(), 800, 500, 20, BLACK);
	DrawText(" AI Money: ", 700, 550, 20, BLACK);
	DrawText(_AIMoney.c_str(), 830, 550, 20, BLACK);

	DrawText("Enter Your Next Move: ", 400, 650, 20, BLACK);
	if (_tableObj.call == 5)
	{
		DrawText("1) Show          2) Show             3) Raise: ", 300, 600, 20, BLACK);
	}
	else
	{
		DrawText("1) Fold          2) Call             3) Raise: ", 300, 600, 20, BLACK);
	}
	
	EndDrawing();
}