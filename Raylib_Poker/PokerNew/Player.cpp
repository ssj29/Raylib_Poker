#include"Player.h"

Player::Player() {};

Player::Player(std::string name,unsigned int m):playerName(name),playerMoney(m) {}

void Player::SetMoney(unsigned int m)
{
	playerMoney = m;
}

std::string Player::GetName() const
{
	return playerName;
}

unsigned int Player::GetMoney() const
{
	return playerMoney;
}

void Player::InitPlayers()
{

}

void Player::SetResult(bool b)
{
	result = b;
}

bool Player::GetResult()
{
	return Player::result;
}

std::string Player::GetPlayerGameStatus()
{
	return gameStatus;
}

void Player::SetPlayerGameStatus(std::string status)
{
	gameStatus = status;
}

Player::~Player() {};