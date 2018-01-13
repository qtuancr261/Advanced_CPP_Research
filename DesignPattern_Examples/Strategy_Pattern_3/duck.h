#ifndef DUCK_H
#define DUCK_H
#include "behavior/flybehavior.h"
#include "behavior/quackbehavior.h"
class Duck
{
private:
    FlyBehavior* flyBehavior;
    QuackBehavior* quackBehavior;
public:
    Duck(FlyBehavior* flyBehaviorPtr = nullptr, QuackBehavior* quackBehaviorPtr = nullptr);
    void setFlyBehavior(FlyBehavior * const flyPtr);
    string doFly() const;
    void setQuackBehavior(QuackBehavior * const quackPtr);
    string doQuack() const;
    virtual ~Duck();
};

#endif // DUCK_H
