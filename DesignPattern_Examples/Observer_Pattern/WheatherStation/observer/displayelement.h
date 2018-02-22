#ifndef DISPLAYELEMENT_H
#define DISPLAYELEMENT_H
#include <iostream>
#include <iomanip>
#include <QtDebug>
using std::cin;
using std::cout;
using std::endl;
using std::setw;
class DisplayElement
{
public:
    virtual void display() const = 0;
};
#endif // DISPLAYELEMENT_H
