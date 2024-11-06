#pragma once
#include<string>
#include<vector>
#include"Cards.h"

class Player
{
private:
	std::string playerName;
	unsigned int playerMoney = 0;
	std::string gameStatus = "NA";
public:
	Player();
	Player(std::string name,unsigned int m);
	bool result = false;

	~Player();
	std::string GetName() const;
	unsigned int GetMoney() const;
	void SetMoney(unsigned int);
	std::vector<std::string> playerHand;
	void InitPlayers();
	void SetResult(bool);
	bool GetResult();

	void SetPlayerGameStatus(std::string);
	std::string GetPlayerGameStatus();


};