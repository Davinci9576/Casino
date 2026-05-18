#pragma once

#include "Player.h"
#include "Game.h"
#include <string>

class Casino {
private:
    Player player;
    Game game;

public:
    Casino();
    void ShowPlayerStatus();
    bool Authentication();
    void ChangeAccountUI();
    void PlayGame();
    void ShowLeaderBoard();
    void start();
    
};