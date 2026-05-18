#include "Card.h"
#include <string>
using namespace std;

string Card::ValueToString(int value){
    if(value==1) return "A";
    if(value==11) return "J";
    if(value==12) return "Q";
    if(value==13) return  "K";
    return to_string(value);
}
string Card::SuitToString(int suit){
    if(suit==1) return "Spade";
    if(suit==2) return "Heart";
    if(suit==3) return "Diamond";
    if(suit==4) return "Club";
    return "?";
}
string Card::toString() const{
    return ValueToString(value) + SuitToString(suit);
}