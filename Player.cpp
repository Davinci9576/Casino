#include "Player.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

Player::Player(double startingBalance) {
    balance = startingBalance;
    wins = 0;
    losses = 0;
    winrate = 0;
    CurrentBet = 0;
    TotalBet = 50;
    username = "";
    pass = "";
}

Player::Player(string name, string password, double Balance) {
    username = name;
    pass = password;
    balance = Balance;
    wins = 0;
    losses = 0;
    winrate = 0;
    CurrentBet = 0;
    TotalBet = 50;
}

void Player::addCard(Card c) {
    hand.push_back(c);
}

void Player::showHand() {
    for (const Card c : hand) {
        cout << CardToString(c)<<" ";
    }
    cout<<endl;
}

void Player::PerfectTie() {
    balance += TotalBet;
}

void Player::clearHand() {
    hand.clear();
}

void Player::increaseBet(double extraBet) {
    CurrentBet += extraBet;
    balance -= extraBet;
    TotalBet += CurrentBet;
}

double Player::getBalance() {
    return balance;
}

void Player::addBalance() {
    balance += (TotalBet * 2);
}

void Player::subtractBalance() {
    balance -= 50;
}

void Player::addWins() {
    wins++;
}

void Player::addLosses() {
    losses++;
}

void Player::GetWinrate() {
    if ((wins + losses) == 0) {
        winrate = 0;
    } else {
        winrate = ((double)wins / (wins + losses)) * 100;
    }
}

void Player::ResetCurrentBet() {
    CurrentBet = 0;
}

void Player::ResetTotalBet() {
    TotalBet = 50;
}

void Player::ShowStatus(string username) {
    cout << "=======" << username << "========" << endl;
    cout << "Balance: " << balance << endl;
    cout << "Wins: " << wins << endl;
    cout << "Losses: " << losses << endl;
    cout << "Winrate: " << winrate << endl;
}

void Player::gameOver() {
    addLosses();
}

vector<Card> Player::getHand() {
    return hand;
}

void Player::SaveToFile() {
    ofstream file(username + ".txt");
    if (file.is_open()) {
        file << balance << endl;
        file << wins << endl;
        file << losses << endl;
        file << winrate << endl;
        file << pass << endl;
    }
}

void Player::LoadFromFile() {
    ifstream file(username + ".txt");
    if (file.is_open()) {
        file >> balance;
        file >> wins;
        file >> losses;
        file >> winrate;
        file >> pass;
    }
}

bool Player::Password(string passwords) {
    return pass == passwords;
}

void Player::ranking(string username) {
    ofstream file("Ranking.txt", ios::app);
    file << username << endl;
}

void Player::LeaderBoard(int choice) {
    ifstream list("Ranking.txt");
    vector<string> users;
    string name;

    if (list.is_open()) {
        while (list >> name) {
            users.push_back(name);
        }
        list.close();
    }

    struct PlayerData {
        double balance;
        int wins;
        int losses;
        double winrate;
        string username;
    };

    vector<PlayerData> leader;
    PlayerData p;

    for (auto& user : users) {
        ifstream file(user + ".txt");
        if (file.is_open()) {
            file >> p.balance;
            file >> p.wins;
            file >> p.losses;
            file >> p.winrate;
            p.username = user;
            leader.push_back(p);
            file.close();
        }
    }

    if (choice == 1) {
        sort(leader.begin(), leader.end(), [](PlayerData a, PlayerData b) {
            return a.balance > b.balance;
        });
    } else if (choice == 2) {
        sort(leader.begin(), leader.end(), [](PlayerData a, PlayerData b) {
            return a.wins > b.wins;
        });
    } else if (choice == 3) {
        sort(leader.begin(), leader.end(), [](PlayerData a, PlayerData b) {
            return a.winrate > b.winrate;
        });
    } else {
        cout << "Invalid input!" << endl;
        return;
    }

    for (int i = 0; i < leader.size(); i++) {
        cout << i + 1 << ". " << leader[i].username << endl;
    }
}
string Player::ValueToString(int value){
    if(value==1) return "A";
    if(value==11) return "J";
    if(value==12) return "Q";
    if(value==13) return  "K";
    return to_string(value);
}
string Player::SuitToString(int suit){
    if(suit==1) return "Spade";
    if(suit==2) return "Hearth";
    if(suit==3) return "Diamond";
    if(suit==4) return "Club";
    return "?";
}
string Player::CardToString( const Card& c){
    return ValueToString(c.value)+SuitToString(c.suit);
}


void Player::ChangeAccount() {
    string account;
    cout << "Enter the username to change:" << endl;
    cin >> account;

    ifstream file(account + ".txt");

    if (!file.is_open()) {
        cout << "No account is registered under " << account << endl;
        return;
    }

    double prebalance;
    int prewins;
    int prelosses;
    double prewinrate;
    string prepass;

    file >> prebalance >> prewins >> prelosses >> prewinrate >> prepass;
    file.close();

    string pass;
    for (int i = 0; i < 5; i++) {
        cout << "Enter the password:" << endl;
        cin >> pass;

        if (pass == prepass) {
            cout << "Log in successful!" << endl;
            balance = prebalance;
            wins = prewins;
            losses = prelosses;
            winrate = prewinrate;
            username = account;
            this->pass = prepass;
            return;
        } else {
            cout << "Wrong password! (" << 4 - i << " tries left)" << endl;
        }
    }

    cout << "Ran out of attempts!" << endl;
}