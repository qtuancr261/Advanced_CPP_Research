#ifndef QUACKQUACK_H
#define QUACKQUACK_H
#include "quackbehavior.h"

class QuackQuack : public QuackBehavior
{
public:
    QuackQuack();
    virtual string quack() const override;
};

#endif // QUACKQUACK_H
