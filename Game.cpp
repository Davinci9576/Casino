#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(Player& p) : player(p) {}

void Game::startRound() {
    player.clearHand();
    dealer.clearHand();
    communityCards.clear();

    deck.cardBuild();
    deck.shuffleDeck();

    cout << "\n----HOLE CARDS----\n";
    dealHoleCards();
    player.showHand();
    player.ResetTotalBet();

    if (!handAction()) return;

    cout << "====Flop======" << endl;
    dealFlop();
    showCommunity();
    player.showHand();

    if (!handAction()) return;

    cout << "\n=====Turn=====\n";
    dealTurn();
    showCommunity();
    player.showHand();

    if (!handAction()) return;

    cout << "\n=====River=======\n";
    dealRiver();
    showCommunity();
    player.showHand();

    if (!handAction()) return;

    cout << "\n=======SHOWDOWN===========\n";
    showTable();

    auto playerResult = HandEvaluator::evaluate(player.getHand(), communityCards);
    auto dealerResult = HandEvaluator::evaluate(dealer.getHand(), communityCards);

    int result = CompareHands(playerResult, dealerResult);

    player.subtractBalance();

    if (result > 0) {
        cout << "Player won!" << endl;
        player.addBalance();
        player.addWins();
    } else if (result < 0) {
        cout << "Computer won!" << endl;
        player.addLosses();
    } else {
        cout << "Perfect tie!" << endl;
        player.PerfectTie();
    }

    player.GetWinrate();
}

bool Game::handAction() {
    choice = playerAction();

    if (choice == 1) return true;

    else if (choice == 2) {
        player.ResetCurrentBet();
        increaseBet();
        return true;
    }

    else if (choice == 3) {
        player.gameOver();
        return false;
    }

    cout << "Invalid input!" << endl;
    return false;
}

int Game::CompareHands(const HandEvaluator::HandResult& a,
                       const HandEvaluator::HandResult& b) {

    if (a.rank > b.rank) return 1;
    if (b.rank > a.rank) return -1;

    for (size_t i = 0; i < a.values.size(); i++) {
        if (a.values[i] > b.values[i]) return 1;
        if (b.values[i] > a.values[i]) return -1;
    }

    return 0;
}

void Game::dealHoleCards() {
    for (int i = 0; i < 2; i++) {
        player.addCard(deck.dealCard());
        dealer.addCard(deck.dealCard());
    }
}

void Game::dealFlop() {
    for (int i = 0; i < 3; i++) {
        communityCards.push_back(deck.dealCard());
    }
}

void Game::dealTurn() {
    communityCards.push_back(deck.dealCard());
}

void Game::dealRiver() {
    communityCards.push_back(deck.dealCard());
}

void Game::showCommunity() {
    cout << "\nCommunity Cards:\n";
    for (auto& c : communityCards) {
        cout << c.value << " " << c.suit << endl;
    }
}

void Game::showTable() {
    cout << "Player cards:\n";
    player.showHand();

    cout << "\nComputer cards:\n";
    dealer.showHand();

    cout << "\nCommunity cards:\n";
    showCommunity();
}

void Game::increaseBet() {
    double extraBet;

    while (true) {
        cout << "Enter the extra bet:" << endl;
        cin >> extraBet;

        if (extraBet + 50 <= player.getBalance()) break;

        cout << "Insufficient balance, try again!" << endl;
    }

    player.increaseBet(extraBet);
}

int Game::playerAction() {
    int choice;

    cout << "Choose your action:\n";
    cout << "1. Check\n2. Bet\n3. Fold\n";
    cout << "Choice: ";

    cin >> choice;
    return choice;
}