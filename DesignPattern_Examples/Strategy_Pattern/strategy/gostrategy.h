#ifndef GOALGORITHM_H
#define GOALGORITHM_H
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
// An example of Strategy Pattern with GoStrategy
// Extract the volatile parts of your code and encapsulate it as objects
class GoStrategy
{
public:
    GoStrategy() = default;
    virtual void go() const = 0;
    virtual ~GoStrategy() = default;
};

#endif // GOALGORITHM_H
