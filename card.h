#pragma once

#include <string>

struct Card {
    int value;
    int suit;

    std::string toString() const;

private:
    static std::string ValueToString(int value);
    static std::string SuitToString(int suit);
};