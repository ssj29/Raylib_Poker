#include"Table.h"
#include"../InitGame.h"

Table::Table()
{
	Deck deckObj;
	tempCards = deckObj.ShuffleDeckFunction();
}

void Table::ShowTableInfo(Table &TableObj,int size)
{
	
	ShowPlayers(TableObj);
	std::cout << "Pot Money = " << TableObj.GetMoney() << std::endl;
	ShowHiddenCards(size);
	for (unsigned int i = 0; i < players.size(); i++)
	{
		std::cout << players.at(i).GetName() << " ";
		ShowCards(players.at(i).playerHand);
	}
}

void Table::SetPlayersCards()
{
	int random = 0;
	Cards cardsObj;
	for (unsigned int i = 0; i < players.size(); i++)
	{
		
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(0, 51);
		std::string temp;
		for (int j = 0; j < 2; j++)
		{
			temp = tempCards.back();
			players.at(i).playerHand.push_back(temp);
			tempCards.pop_back();
		}
	}
}

void Table::SetPlayers(Table& TableObj)
{
	Player * player1 = new Player("Real_Player", 100);
	Player * player2 = new Player("Computer", 100);
	TableObj.players.push_back(* player1);
	TableObj.players.push_back(* player2);
	
}

void Table::ShowPlayers(Table& TableObj)
{
	for (unsigned int i = 0; i < TableObj.players.size(); i++)
	{
		std::cout << "Player " << i <<" Name :" << players.at(i).GetName() << std::endl;
		std::cout << "Player " << i <<" Money:" << players.at(i).GetMoney() << std::endl;
	}
	std::cout << "Please wait....."<< std::endl;
}

void Table::SetHiddenCards(Table& TableObj)
{
	Cards cardsObj;
	
	std::string temp;
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, 51);
	//int random = 0;
	for (int i = 0; i < 5; i++)
	{
		//random = distr(gen);
		//TableObj.hiddenCards.push_back(tempCards.at(random));
		temp = tempCards.back();
		TableObj.hiddenCards.push_back(temp);
		tempCards.pop_back();
	}
}

void Table::setMoney(int m)
{
	money = m;
}

void Table::ShowHiddenCards(int size)
{
	std::cout << "Table Cards is : [";
	for (int i = 0; i < size; i++)
	{
		std::cout<<" "<< hiddenCards.at(i)<<", ";
	}
	std::cout << " ]"<<std::endl;
	std::cout << std::endl;

}

void Table::TableInit(Table &TableObj)
{
	TableObj.setMoney(0);
	TableObj.hiddenCards.clear();
	for (int i = 0; i < TableObj.hiddenCards.size(); i++)
	{
		TableObj.hiddenCards.pop_back();
	}
}

void Table::SetTable(Table& TableObj)
{
	
	MainMenu::ClearScreen();
	TableObj.TableInit(TableObj);
	
	TableObj.SetHiddenCards(TableObj);
	TableObj.SetPlayersCards();
	for (unsigned int i = 0; i < players.size(); i++)
	{
		unsigned int tempMoney = players.at(i).GetMoney();
		players.at(i).SetMoney(tempMoney - 20);
		setMoney(GetMoney() + 20);
	}
	
	int call = 2;
	
	while (choicePlay)
	{	
		std::cout << "..........Table setting up starting........." << std::endl;
		std::cout << "20 Rs will be added in round form both player" << std::endl;
		ShowTableInfo(TableObj, call);
		std::cout << "Enter next move........" << std::endl;
		std::cout << "1) Fold  2) Call  3) Raise" << std::endl;
		//std::cin >> choicePlay;

		switch (choicePlay)
		{
		case 1:
			std::cout << "You choose fold so computer won" << std::endl;
			TableObj.SetWonPlayer(players.at(1), TableObj);
			call = 5;
			choicePlay = 0;
			break;

		case 2:
			if (call < 5)
			{
				call = call + 1;
			}
			if (call == 5)
			{
				std::cout << "Showing Result....." << std::endl;
				choicePlay = 0;
				CheckWinner(players, TableObj);
			}
			break;

		case 3:
			std::cout << "10 Rs will be deducted from the player..." << std::endl;
			if (TableObj.players.at(0).GetMoney() < 10)
			{
				std::cout << "Player does not have enough cash so will declare winnner...." << std::endl;
				std::cout << "1) show" << std::endl;
				CheckWinner(players, TableObj);
				std::cout << "Press Enter to enter the Game..." << std::endl;
				//if (std::cin.get() == '\n') { }
				//choicePlay = 0;
			}
			else
			{
				TableObj.players.at(0).SetMoney(TableObj.players.at(0).GetMoney() - 10);
				TableObj.setMoney(TableObj.GetMoney() + 10);
			}
			break;

			default:
			{
				std::cout << "Enter correct option" << std::endl;
				break;
			}
		}
		
		MainMenu::ClearScreen();
	}

	system("cls");
	int repeatGame = 0;
	std::cout << "Do you want to play again ?" << std::endl;
	std::cout << "1) Yes    2) No" << std::endl;
	//std::cin >> repeatGame;
	if (1 == repeatGame)
	{
		if(TableObj.players.at(0).GetMoney() >= 20)
		{ 
			for (unsigned int i = 0; i < TableObj.players.size(); i++)
			{
				Player &playerObj = TableObj.players.at(i);
				playerObj.playerHand.clear();
			}
			TableObj.TableInit(TableObj);
			
			TableObj.ShowPlayers(TableObj);
			TableObj.SetTable(TableObj);
		}
		else
		{
			std::cout << "Player Does not have cash so cannot play" << std::endl;
			exit(0);
		}
	}	
}

int Table::SetRank(Player& playerObj, Table& TableObj)
{
	std::vector<std::string> allHandTableCards;
	std::vector<char> numbers;
	std::vector<char> cardSuite;
	std::vector<int> CardsNumbers;
	int seq = 0;
	
	for (unsigned int i = 0; i < playerObj.playerHand.size(); i++)
	{
		allHandTableCards.push_back(playerObj.playerHand.at(i));
	}
	for (unsigned int i = 0; i < TableObj.hiddenCards.size(); i++)
	{
		allHandTableCards.push_back(TableObj.hiddenCards.at(i));
	}
	std::cout << "" << playerObj.GetName() << " Cards: ";
	ShowCards(allHandTableCards);

	int cardType = 0, cardNumber = 0;

	for (unsigned int i = 0; i < allHandTableCards.size(); i++)
	{
		numbers.push_back(allHandTableCards.at(i).back());
		cardSuite.push_back(allHandTableCards.at(i).front());
	}
	for (unsigned int i = 0; i < numbers.size(); i++)
	{
		if ('A' == numbers.at(i))
		{
			CardsNumbers.push_back(1);
		}
		else if ('J' == numbers.at(i))
		{
			CardsNumbers.push_back(11);
		}
		else if ('Q' == numbers.at(i))
		{
			CardsNumbers.push_back(12);
		}
		else if ('K' == numbers.at(i))
		{
			CardsNumbers.push_back(13);
		}
		else
		{
			CardsNumbers.push_back(numbers.at(i) - '0');
		}
	}
	sort(CardsNumbers.begin(), CardsNumbers.end());
	sort(cardSuite.begin(), cardSuite.end());

	int duplicateCount = 0, duplicateSuite = 0;
	
	for (int i = 0; i < 7; i++)
	{
		int temp = 0;
		temp = std::count(CardsNumbers.begin(), CardsNumbers.end(),CardsNumbers.at(i));
		if (temp > duplicateCount)
		{
			duplicateCount = temp;
		}
	}

	if (duplicateCount >= 4 && duplicateSuite >= 4 && CardsNumbers.at(6)==13)
	{
		return 1;
	}
	else if (duplicateCount >= 3 && duplicateSuite >= 3)
	{
		return 2;
	}
	else if (duplicateCount >= 4)
	{
		return 3;
	}
	else if (duplicateCount >= 3)
	{
		return 4;
	}
	else if (duplicateSuite >= 4)
	{
		return 5;
	}
	else if (duplicateCount >= 4)
	{
		return 6;
	}

	else if (duplicateCount >= 2)
	{
		return 7;
	}
	else if ( duplicateCount >= 1)
	{
		return 8;
	}
	else if (13 == CardsNumbers.back())
	{
		return 9;
	}
	else if (12 == CardsNumbers.back())
	{
		return 10;
	}
	return 0;
}

int Table::CheckWinner(std::vector<Player> PlayerObj, Table& TableObj)
{
	std::cout << "Checking Winner..... " << std::endl;
	std::vector<int> rank;
	for (unsigned int i = 0; i < players.size(); i++)
	{
		rank.push_back(TableObj.SetRank(players.at(i),TableObj));
	}
	//int min = std::distance(std::begin(rank), std::min_element(std::begin(rank), std::end(rank)));

	int min = 100;
	if (rank.at(0) < rank.at(1))
	{
		min = 0;
	}
	/*else if (rank.at(0) == rank.at(1))
	{
		std::cout << "match is Draw..." << std::endl;
		int potMoneyDevide = TableObj.GetMoney()/2;
		TableObj.setMoney(potMoneyDevide);
		min = 0;
	}*/
	else
	{
		min = 1;
	}
	std::cout << std::endl;
	std::cout << "Next screen in 2 seconds..... " << std::endl;
	//Sleep(3500);

	SetWonPlayer(TableObj.players.at(min), TableObj);
	return 0;
}

unsigned int Table::GetMoney()
{
	return money;
}

void Table::ShowCards(std::vector<std::string> &vec)
{
	std::cout << "[ ";
	for (unsigned int i = 0; i < vec.size(); i++)
	{
		std::cout << vec.at(i) << ", ";
	}
	std::cout << " ]" << std::endl;
}

void Table::SetWonPlayer(Player& playerObj, Table& TableObj)
{
	playerObj.SetMoney(playerObj.GetMoney() + TableObj.GetMoney());
}

std::vector<Player> Table::GetPlayers()
{
	return players;
}

std::vector<std::string> Table::GetHiddenCards()
{
	return hiddenCards;
}

void Table::GamePlay(Table &TableObj, Player &_player1Obj, Player &_player2Obj)
{
	
	while (TableObj.choicePlay)
	{
		switch (TableObj.choicePlay)
		{
			case 1:
			{
				std::cout << "You choose fold so computer won" << std::endl;
				SetWonPlayer(_player2Obj, TableObj);
				TableObj.call = 5;
				TableObj.choicePlay = 2;
				break;
			}

			case 2:
			{
				if (TableObj.call < 5)
				{
					TableObj.call = TableObj.call + 1;
					TableObj.choicePlay = 0;
				}
				if (TableObj.call == 5)
				{
					int player1Rank = 100;
					int player2Rank = 100;
					TableObj.choicePlay = 0;
					player1Rank= TableObj.SetRank(_player1Obj, TableObj);
					player2Rank = TableObj.SetRank(_player2Obj, TableObj);

					if (player1Rank > player2Rank)
					{
						TableObj.SetWonPlayer(_player1Obj, TableObj);
						_player1Obj.SetPlayerGameStatus("WON");
						_player2Obj.SetPlayerGameStatus("LOOSE");
					}
					else
					{
						TableObj.SetWonPlayer(_player2Obj, TableObj);
						_player1Obj.SetPlayerGameStatus("LOOSE");
						_player2Obj.SetPlayerGameStatus("WON");
					}
				}
				break;
			}


			case 3:
			{
				std::cout << "10 Rs will be deducted from the player..." << std::endl;
				if (_player1Obj.GetMoney() < 10)
				{
					TableObj.choicePlay = 2;
					TableObj.call = 5;
				}
				else
				{
					_player1Obj.SetMoney(_player1Obj.GetMoney() - 10);
					TableObj.setMoney(TableObj.GetMoney() + 10);
					TableObj.choicePlay = 0;
				}
				break;
			}

			default:
			{
				std::cout << "Enter correct option" << std::endl;
				break;
			}
		}
	}
}

int Table::GetRank()
{
	return rank;
}

void Table::SetPlayerCards(Player &_playerObj)
{
	int random = 0;
	Cards cardsObj;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(0, 51);
	std::string temp;
	for (int j = 0; j < 2; j++)
	{
		temp = tempCards.back();
		_playerObj.playerHand.push_back(temp);
		tempCards.pop_back();
	}
}

