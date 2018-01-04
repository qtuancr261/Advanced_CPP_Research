#include "player.h"
Player::Player(int newHPValue, int newLevel, std::__cxx11::string newName)
    : hitPoint{newHPValue}, level{newLevel}, name{newName}
{
    // Nothing to do here . I love c++11 initializer uniform
    cout << "New Player was created by Player default constructor" << endl;
}

void Player::setHP(int newValue)
{
    hitPoint = newValue;
}

int Player::getHP() const
{
    return hitPoint;
}

void Player::setLevel(int newLevel)
{
    level = newLevel;
}

int Player::getLevel() const
{
    return level;
}

void Player::changeName(string newName)
{
    name = newName;
}

std::__cxx11::string Player::getName() const
{
    return name;
}

void Player::showInfo() const
{
    cout << "Player's name: " << name << endl;
    cout << "Max HP: " << hitPoint << endl;
    cout << "Current Level: " << level << endl;
}

void Player::testLocalPointer(const Player srcPlayer)
{
    auto desPlayer = make_unique<Player>(srcPlayer);
    desPlayer->showInfo();
}
Player::~Player()
{
    cout << name  + " Object was deleted by smart pointer. " << endl;
}


