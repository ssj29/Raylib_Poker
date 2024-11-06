#pragma once
#include<vector>
#include<string>
#include <algorithm>
#include <random>
#include"Cards.h"

class Deck
{
private:

public:
	Deck();
	~Deck();

	std::vector<std::string> ShuffleDeckFunction();
};