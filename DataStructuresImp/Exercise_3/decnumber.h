#ifndef DECIMALNUMBER_H
#define DECIMALNUMBER_H
#include "number.h"
class DecNumber : public Number
{
public:
    explicit DecNumber(int value);
    virtual void printIt() const override;
};

#endif // DECIMALNUMBER_H
