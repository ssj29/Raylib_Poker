#pragma once
#include"raylib.h"
#include"pokernew/MainMenu.h"
#include<string>
#include<memory>

typedef enum GameScreen { WELCOMEPAGE = 0, MENU, INGAME, INGAME1, ENDING, HISTORY } GameScreen;

class InitGame 
{
private:
	const int ScreenWidth = 1080;
	const int ScreenHieght = 720;
	GameScreen currentScreen = WELCOMEPAGE;
	char name[10];
	
public:
	Table* _tableObj;
	Player _player1Obj;
	Player _player2Obj;
	std::string DBName;

	InitGame();
	void InitState();
	void SetCurrentState(GameScreen);
	GameScreen GetCurrentState();
	Table GetTableObj();
	void SetTableObj(Table*);

	void StartSQL();
	void InsertSQL();

	~InitGame();
};