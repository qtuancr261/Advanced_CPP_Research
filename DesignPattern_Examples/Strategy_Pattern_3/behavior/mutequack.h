#ifndef MUTEQUACK_H
#define MUTEQUACK_H
#include "quackbehavior.h"

class MuteQuack : public QuackBehavior
{
public:
    MuteQuack();
    virtual string quack() const override;
};

#endif // MUTEQUACK_H
