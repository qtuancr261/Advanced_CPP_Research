#include <QCoreApplication>
#include <string>
#include <iostream>
#include <numeric>
#include "player.h"
using std::cout;
using std::endl;
using std::begin;
using std::end;
using std::accumulate;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cout << "Begin using iterator with STL C++" << endl;
    int arrayA[]{15, 24, 7, 105, 120, 1036};
    for (auto iter_begin = std::begin(arrayA); iter_begin != std::end(arrayA); ++iter_begin)
        cout << *iter_begin << " ";
    auto sumA = accumulate(std::begin(arrayA), std::end(arrayA), 0.0);
    cout << endl << "The sum of the array elements is: " << sumA << endl;


    Player tempPlayer;
    cout << std::boolalpha << Player::checkValidPlayer(tempPlayer, "GT210") << endl;
    cout << Player::checkValidPlayer(tempPlayer, "@GymPro121") << endl;
    //Player::checkLevel(tempPlayer, string("GT220"));
    return 0;
    return a.exec();
}
