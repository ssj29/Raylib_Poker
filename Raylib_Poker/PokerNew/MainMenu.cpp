#include"MainMenu.h"

MainMenu::MainMenu()
{

}

void MainMenu::ClearScreen()
{
	//Sleep(2000);
	system("cls");
}

int MainMenu::StartGame()
{
	std::cout << "Game Started" << std::endl;
	std::cout << "Two Players Names are...." << std::endl;
	Table *TableObj = new Table();

	TableObj->TableInit(* TableObj);
	TableObj->SetPlayers(* TableObj);
	TableObj->ShowPlayers(* TableObj);
	TableObj->SetTable(*TableObj);
	
	return 0;
}

int MainMenu::Run()
{
	//std::cout << "--------Welcome to Poker------------"<<std::endl;
	//std::cout << "Press Enter to enter the Game..." << std::endl;
	//if (std::cin.get() == '\n')
	//{
		MainMenu::GameMenu();
	//}
	return 0;
}

int MainMenu::GameMenu()
{
	std::cout << "--------Welcome to Main menu------------" << std::endl;
	std::cout << "Please select the below options" << std::endl;
	std::cout << "1) Start the Game" << std::endl;
	std::cout << "2) Exit the game" << std::endl;
	int choice = 1;

	while (choice)
	{
		std::cin >> choice;
		switch (choice)
		{
		case 1: 
			MainMenu::StartGame();
			std::cout << "Please select 2 to exit the game" << std::endl;
			break;

		case 2: return 0;
			break;
		default:
			std::cout << "Please select 1 or 2 option" << std::endl;
			break;
		}
	}
	return 0;
}


MainMenu::~MainMenu()
{

}