#pragma once
#include <vector>
#include <string>

class Cards
{
private:

public:
	Cards();
	std::vector<std::string> allCards
	{
		"Hearts_A", "Hearts_2", "Hearts_3", "Hearts_4", "Hearts_5", "Hearts_6", "Hearts_7", "Hearts_8", "Hearts_9", "Hearts_10", "Hearts_J", "Hearts_Q", "Hearts_K",
		"Spades_A", "Spades_2", "Spades_3", "Spades_4", "Spades_5", "Spades_6", "Spades_7", "Spades_8", "Spades_9", "Spades_10", "Spades_J", "Spades_Q", "Spades_K",
		"Diamond_A", "Diamond_2", "Diamond_3", "Diamond_4", "Diamond_5", "Diamond_6", "Diamond_7", "Diamond_8", "Diamond_9", "Diamond_10", "Diamond_J", "Diamond_Q", "Diamond_K",
		"Clubs_A", "Clubs_2", "Clubs_3", "Clubs_4", "Clubs_5", "Clubs_6", "Clubs_7", "Clubs_8", "Clubs_9", "Clubs_10", "Clubs_J", "Clubs_Q", "Clubs_K",
	};
};