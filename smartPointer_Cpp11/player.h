#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>
#include <QScopedPointer>
#include <memory>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::make_unique;
using std::unique_ptr;
class Player
{
private:
    int hitPoint;
    int level;
    string name;
public:
    explicit Player(int newHPValue = 100, int newLevel = 1, string newName = "Tux Player");
    Player(const Player& srcPlayer) = default;
    Player& operator =(const Player& srcPlayer) = default;
    void setHP(int newValue);
    int getHP() const;
    void setLevel(int newLevel);
    int getLevel() const;
    void changeName(string newName);
    string getName() const;
    void showInfo() const;
    static void testLocalPointer(const Player srcPlayer);
    ~Player();
};


#endif // PLAYER_H
