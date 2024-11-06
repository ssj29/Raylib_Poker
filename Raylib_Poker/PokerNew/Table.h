#pragma once
#include<iostream>
#include<vector>
#include<cstdlib>
#include"Cards.h"
#include"Player.h"
#include"MainMenu.h"
#include"Deck.h"
#include<memory>
#include<set>
#include<algorithm>

class Table : public Player
{
private: 
	unsigned int money = 0;
	std::vector<Player> players;
	std::vector<std::string> hiddenCards;
	std::vector<int> checkDuplicate;
	std::vector<std::string> tempCards;
	Table tableObj();
	int rank = 99;

public:
	int call = 2;
	int choicePlay = 0;
	Table();
	void TableInit(Table&);
	void setMoney(int);
	unsigned int GetMoney();
	void SetHiddenCards(Table&);
	void SetPlayers(Table&);
	void ShowPlayers(Table&);
	void SetTable(Table&);
	void SetPlayersCards();
	void ShowCards(std::vector<std::string>&);
	int CheckWinner(std::vector<Player>,Table&);
	void SetWonPlayer(Player&, Table&);
	void ShowHiddenCards(int size);
	int SetRank(Player&, Table&);
	void ShowTableInfo(Table&, int);
	void ShowWinnerStatus();
	std::vector<Player> GetPlayers();
	std::vector<std::string> GetHiddenCards();
	void GamePlay(Table&,Player&,Player&);
	
	int GetRank();
	void SetPlayerCards(Player&);

};