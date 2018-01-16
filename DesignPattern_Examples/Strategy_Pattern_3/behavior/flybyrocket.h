#ifndef FLYBYROCKET_H
#define FLYBYROCKET_H
#include "flybehavior.h"

class FlyByRocket : public FlyBehavior
{
public:
    FlyByRocket();
    virtual string fly() const override;
};

#endif // FLYBYROCKET_H
