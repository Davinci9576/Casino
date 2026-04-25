#pragma once

#include <vector>
#include <string>
#include "Card.h"

class Player {
private:
    std::vector<Card> hand;
    std::string username;
    std::string pass;
    double balance;
    int wins;
    double winrate;
    int losses;
    double CurrentBet;
    double TotalBet;
    static std::string ValueToString(int value);
    static std::string SuitToString(int suit);
    static std::string CardToString(const Card &c);

public:
    Player(double startingBalance = 1000);
    Player(std::string name, std::string password, double Balance = 1000);

    void addCard(Card c);
    void showHand();
    void PerfectTie();
    void clearHand();
    void increaseBet(double extraBet);

    double getBalance();
    void addBalance();
    void subtractBalance();

    void addWins();
    void addLosses();
    void GetWinrate();

    void ResetCurrentBet();
    void ResetTotalBet();

    void ShowStatus(std::string username);
    void gameOver();

    std::vector<Card> getHand();

    void SaveToFile();
    void LoadFromFile();
    bool Password(std::string passwords);

    void ranking(std::string username);
    void LeaderBoard(int choice);
    void ChangeAccount();
};