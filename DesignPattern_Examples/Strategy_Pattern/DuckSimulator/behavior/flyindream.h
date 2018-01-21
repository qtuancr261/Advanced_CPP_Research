#ifndef FLYINDREAM_H
#define FLYINDREAM_H
#include "flybehavior.h"

class FlyInDream : public FlyBehavior
{
public:
    FlyInDream();
    virtual string fly() const override;
};

#endif // FLYINDREAM_H
