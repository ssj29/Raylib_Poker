#include"InitGame.h"
#include "WelcomePage.h"
#include"MenuPage.h"
#include"InGamePage.h"
#include"EndingPage.h"
#include"HistoryPage.h"
#include"sqlite/sqlite3.h"

InitGame::InitGame()
{
	Table* tableObj = new Table();
	InitGame::SetTableObj(tableObj);
	tableObj->TableInit(*tableObj);
	tableObj->SetPlayers(*tableObj);

	InitGame::_player1Obj = _tableObj->GetPlayers().at(0);
	InitGame::_player1Obj.SetMoney(100);
	InitGame::_player2Obj = _tableObj->GetPlayers().at(1);
	InitGame::_player2Obj.SetMoney(100);
	InitGame::DBName = "SaveGames.db";
}

void InitGame::InitState()
{
	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	//const char* constStr = "Hello, World!";
	std::string str(InitGame::DBName);
	char* nonConstStr = &str[0];
	rc = sqlite3_open(nonConstStr, &db);

	//InitGame::StartSQL();

	if (rc)
	{
		std::cout << "canot open DB " << sqlite3_errmsg(db);
	}

	else
	{
		std::cout << "open DB successfully " << sqlite3_errmsg(db);
	}

	InitWindow(ScreenWidth, ScreenHieght, "Poker");
	InitAudioDevice();
	Sound CoinStash = LoadSound("Sound/CoinStash.mp3");
	Sound DrawCard = LoadSound("Sound/DrawCard.mp3");
	Sound EndGame = LoadSound("Sound/EndGame.mp3");

	WelcomePage* welcomeObj = new WelcomePage();
	MenuPage* menuObj = new MenuPage();
	InGamePage* inGamePageObj = new InGamePage();
	EndingPage* endingPageObj = new EndingPage();
	HistoryPage* historyPageObj = new HistoryPage();
	
	while (!WindowShouldClose())
	{
		switch (InitGame::currentScreen)
		{
			case WELCOMEPAGE:
			{
				//std::unique_ptr<WelcomePage> welcomeObj(new WelcomePage);
				
				welcomeObj->SetWelcomePage();
				if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
				{
					InitGame::currentScreen = MENU;
				}
				break;
			}

			case MENU:
			{
				//std::unique_ptr<MenuPage> menuObj(new MenuPage);
				menuObj->SetMenuPage();

				if (IsKeyPressed(KEY_BACKSPACE))
				{
					InitGame::currentScreen = WELCOMEPAGE;
				}

				else if (IsKeyPressed(KEY_KP_1) || IsKeyPressed(KEY_ONE))
				{
					InitGame::currentScreen = INGAME;
				}

				else if (IsKeyPressed(KEY_KP_2) || IsKeyPressed(KEY_TWO))
				{
					InitGame::currentScreen = HISTORY;
				}

				else if (IsKeyPressed(KEY_KP_3) || IsKeyPressed(KEY_THREE))
				{
					CloseWindow();
				}
				break;
			}
			
			case INGAME:
			{
				//std::unique_ptr<InGamePage> inGamePageObj(new InGamePage);
				inGamePageObj->SetInGamePage();

				if (IsKeyPressed(KEY_KP_1) || IsKeyPressed(KEY_ONE))
				{
					InitGame::currentScreen = INGAME;
				}
				
				_tableObj->SetPlayerCards(_player1Obj);
				_tableObj->SetPlayerCards(_player2Obj);
				_tableObj->SetTable(*_tableObj);
				_tableObj->SetHiddenCards(*_tableObj);
				_player1Obj.SetMoney(_player1Obj.GetMoney() - 20);
				_player2Obj.SetMoney(_player2Obj.GetMoney() - 20);
				//setMoney(GetMoney() + 20);

				if (_player1Obj.GetMoney() < 20)
				{
					InitWindow(200, 150, "Warning");
					while (!WindowShouldClose())
					{
					}
				}
				WaitTime(1.0);
				InitGame::SetCurrentState(INGAME1);
				break;
			}

			case INGAME1:
			{
				inGamePageObj->UpdateInGamePage(*_tableObj,_player1Obj,_player2Obj);
				if (IsKeyPressed(KEY_KP_1) || IsKeyPressed(KEY_ONE))
				{
					_tableObj->choicePlay = 1;
					_player2Obj.SetPlayerGameStatus("WON");
					_player1Obj.SetPlayerGameStatus("LOOSE");
					inGamePageObj->UpdateInGamePage(*_tableObj, _player1Obj, _player2Obj);
					InitGame::SetCurrentState(ENDING);
				}

				if (IsKeyPressed(KEY_KP_2) || IsKeyPressed(KEY_TWO))
				{
					PlaySound(DrawCard);
					_tableObj->choicePlay = 2;
					//_tableObj->call = _tableObj->call + 1;
					if (_tableObj->call == 5)
					{
						InitGame::SetCurrentState(ENDING);
					}
				}

				if (IsKeyPressed(KEY_KP_3) || IsKeyPressed(KEY_THREE))
				{
					PlaySound(CoinStash);
					_tableObj->choicePlay = 3;
				}
				break;
			}
			
			case ENDING:
			{
				endingPageObj->SetEndingPage(*_tableObj, _player1Obj, _player2Obj);
				//PlaySound(CoinStash);
				if (IsKeyPressed(KEY_BACKSPACE))
				{
					InitGame::InsertSQL();

					InitGame::SetCurrentState(WELCOMEPAGE);
					_tableObj->setMoney(0);
					_tableObj->TableInit(*_tableObj);
					_tableObj->call = 2;
					_player1Obj.SetPlayerGameStatus("NA");
					_player2Obj.SetPlayerGameStatus("NA");
					_player1Obj.playerHand.clear();
					_player2Obj.playerHand.clear();

					sqlite3_close(db);
				}
				break;
			}

			case HISTORY:
			{
				historyPageObj->SetHistoryPage();
				if (IsKeyPressed(KEY_BACKSPACE))
				{
					InitGame::currentScreen = MENU;
				}
				break;
			}

			default:
			{
				CloseWindow();
			}
		}
		
	}
	delete welcomeObj;
	delete menuObj;
	delete inGamePageObj;
	delete endingPageObj;

	UnloadSound(EndGame);
	UnloadSound(DrawCard);
	UnloadSound(CoinStash);
	CloseAudioDevice();
}

void InitGame::SetCurrentState(GameScreen _currentScreen)
{
	InitGame::currentScreen = _currentScreen;
}

GameScreen InitGame::GetCurrentState()
{
	return InitGame::currentScreen;
}

Table InitGame::GetTableObj()
{
	return *_tableObj;
}

void InitGame::SetTableObj(Table *tObj)
{
	InitGame::_tableObj = tObj;
}


void InitGame::StartSQL()
{
	sqlite3* db;
	std::string str(InitGame::DBName);
	char* DBName = &str[0];
	int _connect;
	char* messaggeError;
	int rc = sqlite3_open(DBName, &db);

	std::string sql;
	sql = "CREATE TABLE Players("  \
		"ID INT PRIMARY KEY     NOT NULL AUTO_INCREMENT," \
		"NAME           TEXT    NOT NULL," \
		"Money          INT     NOT NULL," \
		"Result         TEXT    NOT NULL," \
		"Time           TEXT    NOT NULL," \
		"); ";

	std::string strQuery(sql);
	char* strQuery2 = &strQuery[0];

	_connect = sqlite3_exec(db, strQuery2, NULL, 0, &messaggeError);

	if (_connect != SQLITE_OK) 
	{
		sqlite3_free(messaggeError);
		std::cout << "Connection successfull"<<std::endl;
	}
	else
	{
		std::cout << "Connection UNsuccessfull" << std::endl;
	}
		
}

void InitGame::InsertSQL()
{
	sqlite3* db;
	std::string str1(InitGame::DBName);
	char* DBName = &str1[0];
	int _connect;
	char* messaggeError;

	int rc = sqlite3_open(DBName, &db);
	if (rc != SQLITE_OK)
	{
		std::cout << "Sqlite is NOT connected to DB"<<std::endl;
		//sqlite3_free(&messaggeError);
	}
	else
	{
		std::cout << "Sqlite is connected to DB" << std::endl;
	}

	std::string sql;
	sql = "CREATE TABLE NewPlayers(ID TEXT, NAME TEXT, Money TEXT, Result TEXT, Time TEXT);";

	std::string strQuery(sql);
	char* strQuery2 = &strQuery[0];

	_connect = sqlite3_exec(db, strQuery2, NULL, 0, &messaggeError);

	if (_connect != SQLITE_OK)
	{
		std::cout << "Table Is NOT created" << std::endl;
		sqlite3_free(messaggeError);
	}
	else
	{
		std::cout << "Table is created" << std::endl;
	}

	std::string sqlInsert;
	std::string tableInfo = "INSERT INTO NewPlayers (ID,NAME,Money,Result,Time) ";
	std::string values1 = "(1,'" + _player1Obj.GetName() + "'," + std::to_string(_player1Obj.GetMoney()) + ",'" + _player1Obj.GetPlayerGameStatus() + "', CURRENT_TIMESTAMP);";
	std::string values2 = "(2,'" + _player2Obj.GetName() + "'," + std::to_string(_player2Obj.GetMoney()) + ",'" + _player2Obj.GetPlayerGameStatus() + "', CURRENT_TIMESTAMP);";

	sqlInsert = tableInfo + "VALUES " + values1 + tableInfo + "VALUES " + values2;

	std::string strQuery_3(sqlInsert);
	char* strQuery3 = &strQuery_3[0];

	_connect = sqlite3_exec(db, strQuery3, NULL, 0, &messaggeError);

	if (_connect != SQLITE_OK) 
	{
		std::cerr << "Table values Insertion Error" << std::endl;
		sqlite3_free(messaggeError);
	}
	else
	{
		std::cerr << "Table values Insertion Successfull" << std::endl;
		//std::cout << "Table created Successfully" << std::endl;
	}
}

InitGame::~InitGame()
{
}
