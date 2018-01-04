#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <cstdlib>
#include <string>
#include "dlist.h"
using std::cin;
using std::cout;
using std::system;
using std::string;
class Menu
{
private:
    string mainMenuContent;
    DList<int> dataList;
    int mainMenuSelection;
public:
    Menu();
    void initMenu();
};

#endif // MENU_H
