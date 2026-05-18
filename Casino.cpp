#include "Casino.h"
#include <iostream>
#include <fstream>
#include "API.h"
using namespace std;

Casino::Casino() : player(), game(player) {}

bool Casino::Authentication() {
    string answer, username;

    cout << "=======Welcome to the Casino!=======" << endl;
    cout << "Do you have an account? (Yes/No)" << endl;

    while (true) {
        cin >> answer;

        for (auto &c : answer) c = tolower(c);

        if (answer == "yes" || answer == "no") break;

        cout << "Invalid input try again." << endl;
    }

    if (answer == "yes") {
        cout << "Enter the username:" << endl;
        cin >> username;

        for (auto &c : username) c = tolower(c);

        ifstream file(username + ".txt");

        if (file.is_open()) {
            player = Player(username, "");
            player.LoadFromFile();

            string pass;

            for (int i = 0; i < 5; i++) {
                cout << "Enter the password:" << endl;
                cin >> pass;

                if (player.Password(pass)) {
                    cout << "Log in successful!" << endl;
                    ApiService api;
                    bool success=api.login(username, pass);
                    if(success){
                        cout<<"Login successful!"<<endl;
                    }else{
                        cout<<"Login failed!"<<endl;
                    }
                    return true;
                } else {
                    cout << "Wrong password! (You have " << 4 - i << " try(s) left)" << endl;
                }
            }

            return false;
        } else {
            cout << "No account exists under " << username << "!" << endl;
            return false;
        }
    }

    else {
        string pass;

        cout << "Enter the username:" << endl;
        cin >> username;

        cout << "Enter the new password:" << endl;
        cin >> pass;

        player = Player(username, pass);
        player.ranking();
        player.SaveToFile();

        cout << "Created a new account!" << endl;
        ApiService api;
        bool success=api.registerUser(username, pass);
        if(success){
            cout<<"Registered successfully!"<<endl;
        }else{
            cout<<"Registration failed!"<<endl;
        }
        return true;
    }
}
void Casino::ChangeAccountUI(){
    string username;
    string password;
    cout<<"Enter the username:"<<endl;
    cin>>username;
    for(int i=0; i<5; i++){
        cout<<"Enter the password:"<<endl;
        cin>>password;
        if(player.LoadAccount(username, password)){
            cout<<"Log in successful!"<<endl;
            return;
        }
        cout<<4-i<<" attempts left to try!"<<endl;
    }
    cout<<"Ran out of try!"<<endl;
}
void Casino::ShowPlayerStatus(){
    cout<<"========="<<player.UsernameGive()<<"======="<<endl;
    cout<<"Balance: "<<player.BalanceGive()<<endl;
    cout<<"Wins: "<<player.WinsGive()<<endl;
    cout<<"Losses: "<<player.LossesGive()<<endl;
    cout<<"Winrate: "<<player.WinrateGive()<<endl;
}
void Casino::ShowLeaderBoard(){
    int choice;
    cout<<"Enter the choice: "<<endl;
    cout<<"1. By balance: "<<endl;
    cout<<"2. By Wins: "<<endl;
    cout<<"3. By Winrate: "<<endl;
    cin>>choice;
    vector <PlayerData> leaders=player.GetLeaderBoard(choice);
    if(leaders.empty()){
        cout<<"Invalid choice!"<<endl;
        return;
    }
    for(int i=0; i<leaders.size(); i++){
        cout<<i+1<<". "<<leaders[i].username<<endl;
    }
}
void Casino::PlayGame() {
    game.startRound();
}

void Casino::start() {
    if (!Authentication()) return;

    int answer;

    while (true) {
        cout << "=====Texas Poker!=====" << endl;
        cout << "1. Play the game!" << endl;
        cout << "2. Show status." << endl;
        cout << "3. Leader Board!" << endl;
        cout << "4. Change the account." << endl;
        cout << "5. Exit the game." << endl;

        cin >> answer;

        if (answer == 1) {
            PlayGame();
            player.SaveToFile();
            player.UpdateRanking();
            player.DefaultBet();

        } else if (answer == 2) {
            ShowPlayerStatus();

        } else if (answer == 3) {
            ShowLeaderBoard();
            cout<<"\n ====ONLINE LEADERBOARD==="<<endl;
            ApiService api;
            string leaderboard=api.fetchLeaderboard();
            cout<<"================"<<endl;
            cout<<leaderboard<<endl;

        } else if (answer == 4) {
            player.SaveToFile();
            ChangeAccountUI();
            player.UpdateRanking();

        } else if (answer == 5) {
            cout << "GoodBye!" << endl;
            player.SaveToFile();
            player.UpdateRanking();
            break;

        } else {
            cout << "Invalid input!" << endl;
        }
    }
}