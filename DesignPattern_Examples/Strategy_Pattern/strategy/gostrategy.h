#ifndef GOALGORITHM_H
#define GOALGORITHM_H
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
class GoStrategy
{
public:
    virtual void go() const = 0;
};

#endif // GOALGORITHM_H
