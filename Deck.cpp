#include "Deck.h"
#include <algorithm>
#include <random>

using namespace std;

Deck::Deck() {
    cardBuild();
}

void Deck::cardBuild() {
    cards.clear();
    for (int v = 1; v <= 13; v++) {
        for (int s = 1; s <= 4; s++) {
            cards.push_back({v, s});
        }
    }
}

void Deck::shuffleDeck() {
    static random_device rd;
    static mt19937 g(rd());
    shuffle(cards.begin(), cards.end(), g);
}

Card Deck::dealCard() {
    Card c = cards.back();
    cards.pop_back();
    return c;
}