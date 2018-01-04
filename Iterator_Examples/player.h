#ifndef PLAYER_H
#define PLAYER_H
#include <QRegExp>
#include <memory>
#include <iostream>
#include <string>
using std::string;
using std::cin;
using std::cout;
class Player
{
private:
   string name;
   int level;
   int basicHitPoints;
public:
   explicit Player(string defaultName = "Player", int defaultLevel = 1);
   ~Player() = default;

   int operator()(int currentLevel)
   {
       return (currentLevel * 100);
   }
   bool operator()(string checkName);
   //static bool checkValidPlayer(Player& player, std::string name);
   template<typename T> static bool checkValidPlayer(Player& P,T type);
};

template<typename T>
bool Player::checkValidPlayer(Player &P, T type)
{
    return P(type);
}

#endif // PLAYER_H
