#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

class Deck {
private:
    std::vector<Card> cards;

public:
    Deck();
    void cardBuild();
    void shuffleDeck();
    Card dealCard();
};

#endif