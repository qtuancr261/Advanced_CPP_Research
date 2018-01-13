#ifndef QUACKBEHAVIOR_H
#define QUACKBEHAVIOR_H
#include <string>
using std::string;
class QuackBehavior
{
public:
    virtual string quack() const = 0;
    virtual ~QuackBehavior() = default;
};
#endif // QUACKBEHAVIOR_H
