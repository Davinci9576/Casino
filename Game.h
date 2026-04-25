#pragma once

#include "Deck.h"
#include "Player.h"
#include "HandEvaluator.h"
#include <vector>

class Game {
private:
    Deck deck;
    Player& player;
    Player dealer;
    std::vector<Card> communityCards;

    bool handAction();
    int CompareHands(const HandEvaluator::HandResult& a,
                     const HandEvaluator::HandResult& b);

    void dealHoleCards();
    void dealFlop();
    void dealTurn();
    void dealRiver();
    void showCommunity();
    void showTable();
    void increaseBet();
    int playerAction();

public:
    int choice;

    Game(Player& p);

    void startRound();
};