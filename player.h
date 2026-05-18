#pragma once

#include <vector>
#include <string>
#include "Card.h"

struct PlayerData{
    double balance;
    int wins;
    int losses;
    double winrate;
    std::string username;
};

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

    // Helper functions
    static std::string ValueToString(int value);
    static std::string SuitToString(int suit);
    static std::string CardToString(const Card &c);

public:
    // Constructors
    Player(double startingBalance = 1000);
    Player(std::string name, std::string password, double Balance = 1000);

    // Game actions
    void addCard(Card c);
    void showHand();
    void PerfectTie();
    void clearHand();
    void increaseBet(double extraBet);
    void DefaultBet();

    // Balance
    double getBalance() const;
    std::string getUsername() const;
    void addBalance();
    void subtractBalance();

    // Stats
    void addWins();
    void addLosses();
    void GetWinrate();

    // Reset
    void ResetCurrentBet();
    void ResetTotalBet();

    double WinrateGive();
    int WinsGive();
    int LossesGive();
    std::string UsernameGive();
    double BalanceGive();
    // Online

    // Status
    void gameOver();

    // Hand
    std::vector<Card> getHand();

    // File handling
    void SaveToFile();
    void LoadFromFile();
    bool Password(std::string passwords);

    // Ranking
    void ranking();
    void UpdateRanking();
    std::vector <PlayerData> GetLeaderBoard(int choice);

    // Account
    bool LoadAccount(std::string account, std:: string passwordInput);
};