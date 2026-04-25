#include "Casino.h"
#include <iostream>
#include <fstream>

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
                    Username = username;  // ✅ important fix
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

        Username = username;

        cout << "Enter the new password:" << endl;
        cin >> pass;

        player = Player(username, pass);
        player.ranking(username);
        player.SaveToFile();

        cout << "Created a new account!" << endl;
        return true;
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

        } else if (answer == 2) {
            player.ShowStatus(Username);

        } else if (answer == 3) {
            int choice;

            cout << "1. By Balance." << endl;
            cout << "2. By Wins." << endl;
            cout << "3. By Win Rate." << endl;

            cin >> choice;
            player.LeaderBoard(choice);

        } else if (answer == 4) {
            player.SaveToFile();
            player.ChangeAccount();

        } else if (answer == 5) {
            cout << "GoodBye!" << endl;
            player.SaveToFile();
            break;

        } else {
            cout << "Invalid input!" << endl;
        }
    }
}