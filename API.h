#pragma once
#include <string>

class Player;
class ApiService
{
    public:
    void sendScore(const Player& player);
    std::string fetchLeaderboard();
    bool login(
        const std::string& username,
        const std::string& password
    );
    bool registerUser(
        const std::string& username,
        const std::string& password
    );
};