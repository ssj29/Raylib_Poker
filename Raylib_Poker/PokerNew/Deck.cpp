#include"Deck.h"
#include <random> 
#include <numeric>  

Deck::Deck()
{

}

std::vector<std::string> Deck::ShuffleDeckFunction()
{
	Cards cardsObj;
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::shuffle(std::begin(cardsObj.allCards), std::end(cardsObj.allCards), engine);
	return cardsObj.allCards;
}

Deck::~Deck()
{

}