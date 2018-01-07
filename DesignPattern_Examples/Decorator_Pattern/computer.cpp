#include "computer.h"

Computer::Computer()
{
    cout << "Computer constructor" << endl;
}

std::string Computer::description() const
{
    cout << "COMPUTER DES CALLED" << endl;
    return string("A computer");
}
