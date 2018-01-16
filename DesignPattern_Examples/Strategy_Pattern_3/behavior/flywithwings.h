#ifndef FLYWITHWINGS_H
#define FLYWITHWINGS_H
#include "flybehavior.h"

class FlyWithWings : public FlyBehavior
{
public:
    FlyWithWings();
    virtual string fly() const override;
};

#endif // FLYWITHWINGS_H
