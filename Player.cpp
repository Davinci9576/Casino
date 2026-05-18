#include "Player.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <curl/curl.h>
#include <string>
#include <sstream>
#include "Card.h"

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

// ================== GAME LOGIC ==================

void Player::addCard(Card c) {
    hand.push_back(c);
}

void Player::showHand() {
    for (const Card c : hand) {
        cout << c.toString()<< " ";
    }
    cout << endl;
}

void Player::PerfectTie() {
    balance += TotalBet;
}

void Player::clearHand() {
    hand.clear();
}

void Player:: DefaultBet(){
    balance-=50;
}
void Player::increaseBet(double extraBet) {
    CurrentBet += extraBet;
    balance -= extraBet;
    TotalBet += CurrentBet;
}

double Player::getBalance() const {
    return balance;
}
string Player::getUsername() const{
    return username;
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
double Player::WinrateGive(){
    return winrate;
}
int Player:: WinsGive(){
    return wins;
}
int Player::LossesGive(){
    return losses;
}
string Player::UsernameGive(){
    return username;
}
double Player::BalanceGive(){
    return balance;
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

void Player::UpdateRanking() {
    ifstream infile("Ranking.txt");
    vector<string> lines;
    string name, password;
    double bal;
    int win, loss;
    double winr;
    bool found = false;

    while (infile >> name >> bal >> win >> loss >> winr >> password) {
        if (name == username) {
            lines.push_back(username + " " +
                            to_string(balance) + " " +
                            to_string(wins) + " " +
                            to_string(losses) + " " +
                            to_string(winrate) + " " + pass);
            found = true;
        } else {
            lines.push_back(name + " " +
                            to_string(bal) + " " +
                            to_string(win) + " " +
                            to_string(loss) + " " +
                            to_string(winr) + " " + password);
        }
    }

    infile.close();

    if (!found) {
        lines.push_back(username + " " +
                        to_string(balance) + " " +
                        to_string(wins) + " " +
                        to_string(losses) + " " +
                        to_string(winrate) + " " + pass);
    }

    ofstream outfile("Ranking.txt");
    for (auto& line : lines) {
        outfile << line << endl;
    }
}

void Player::ranking() {
    ofstream file("Ranking.txt", ios::app);
    file << username << " " << balance << " " << wins << " "
         << losses << " " << winrate << " " << pass << endl;
}
vector <PlayerData> Player::GetLeaderBoard(int choice){
    ifstream list("Ranking.txt");
    vector<string> users;
    string name, password;
    double bal;
    int win, loss;
    double winr;
    while(list>>name>>bal>>win>>loss>>winr>>password){
        users.push_back(name);
    }
    vector<PlayerData> leader;
    for(auto&user: users){
        ifstream file(user+".txt");
        if(file.is_open()){
            PlayerData p;
            file>>p.balance>>p.wins>>p.losses>>p.winrate;
                p.username=user;
                leader.push_back(p);
        }
    }
    if(choice==1){
        sort(leader.begin(), leader.end(), [](const PlayerData&a, const PlayerData&b){
            return a.balance>b.balance;
        });
    }else if(choice==2){
        sort(leader.begin(), leader.end(), [] (const PlayerData&a, const PlayerData&b){
            return a.wins>b.wins;
        });
    }else if(choice==3){
        sort(leader.begin(), leader.end(),[] (const PlayerData &a, const PlayerData &b){
            return a.winrate>b.winrate;
        });
    }
    else{
        return {};
    }
    return leader;
}

bool Player::LoadAccount(string account, string passwordInput){
    ifstream file(account+".txt");
    if(!file.is_open()){
        return false;
    }
    double prebalance;
    int prewins, prelosses;
    double prewinrate;
    string prepass;
    file>>prebalance>>prewins>>prelosses>>prewinrate>>prepass;
    if(prepass==passwordInput){
        balance=prebalance;
        wins=prewins;
        losses=prelosses;
        winrate=prewinrate;
        username=account;
        pass=prepass;
        return true;
    }
    return false;
}