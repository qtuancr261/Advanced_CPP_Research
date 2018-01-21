#include "duck.h"

Duck::Duck(FlyBehavior *flyBehaviorPtr, QuackBehavior *quackBehaviorPtr)
    : flyBehavior{flyBehaviorPtr},
      quackBehavior{quackBehaviorPtr}
{
    // default constructor
}

void Duck::setFlyBehavior(FlyBehavior * const flyPtr)
{
    delete flyBehavior;
    flyBehavior = flyPtr;
}

std::string Duck::doFly() const
{
    return flyBehavior->fly();
}

void Duck::setQuackBehavior(QuackBehavior * const quackPtr)
{
    delete quackBehavior;
    quackBehavior = quackPtr;
}

std::string Duck::doQuack() const
{
    return quackBehavior->quack();
}

Duck::~Duck()
{
    delete flyBehavior;
    delete quackBehavior;
}
