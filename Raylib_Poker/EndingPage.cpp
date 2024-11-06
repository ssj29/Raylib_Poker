#include"EndingPage.h"


EndingPage::EndingPage()
{

}

void EndingPage::SetEndingPage(Table& _tableObj, Player& _player1Obj, Player& _player2Obj)
{
	BeginDrawing();
	ClearBackground(DARKPURPLE);

	std::string _money = std::to_string(_tableObj.GetMoney());
	DrawText(" GAME END ", 410, 100, 40, RAYWHITE);
	DrawText(" Winner is ", 430, 150, 20, RAYWHITE);

	if (_player1Obj.GetPlayerGameStatus() == "WON")
	{
		DrawText(_player1Obj.GetName().c_str(), 560, 150, 20, GREEN);
	}
	else if (_player2Obj.GetPlayerGameStatus() == "WON")
	{
		DrawText(_player2Obj.GetName().c_str(), 560, 150, 20, GREEN);
	}
	DrawText("Player won POT money ", 400, 350, 20, RAYWHITE);
	DrawText(_money.c_str(), 520, 380, 20, RAYWHITE);

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

	DrawText(" Table Cards Below", 450, 190, 20, RAYWHITE);

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
	DrawText(" Player Name: ", 100, 500, 20, RAYWHITE);
	DrawText(_playerName.c_str(), 250, 500, 20, RAYWHITE);
	DrawText(" Player Money: ", 100, 550, 20, RAYWHITE);
	DrawText(_playerMoney.c_str(), 280, 550, 20, RAYWHITE);

	for (int i = 0; i < _player2Obj.playerHand.size(); i++)
	{
		cardPath = "Cards/" + _player2Obj.playerHand.at(i) + ".png";
		Image card = LoadImage(cardPath.c_str());
		ImageResize(&card, 70, 100);
		Texture2D texture = LoadTextureFromImage(card);
		DrawTexture(texture, player2CardsSpace_X, 380, WHITE);
		player2CardsSpace_X += 120;
	}
	DrawText(" AI Name: ", 700, 500, 20, RAYWHITE);
	DrawText(_AIName.c_str(), 800, 500, 20, RAYWHITE);
	DrawText(" AI Money: ", 700, 550, 20, RAYWHITE);
	DrawText(_AIMoney.c_str(), 830, 550, 20, RAYWHITE);

	DrawText("Press Backspace to go Welcome Page...... ", 350, 600, 20, RAYWHITE);
	EndDrawing();
}

EndingPage::~EndingPage()
{

}