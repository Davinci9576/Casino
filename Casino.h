#pragma once

#include "Player.h"
#include "Game.h"
#include <string>

class Casino {
private:
    Player player;
    Game game;
    std::string Username;

public:
    Casino();

    bool Authentication();
    void PlayGame();
    void start();
};