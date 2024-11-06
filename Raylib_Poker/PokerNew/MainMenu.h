#pragma once
#include<iostream>
//#include<windows.h>
#include"Cards.h"
#include"Table.h"
#include"Player.h"
#include<stdio.h>

class MainMenu
{
private:

public:
	MainMenu();
	~MainMenu();
	static int Run();
	static int GameMenu();
	static int StartGame();
	static void ClearScreen();

};