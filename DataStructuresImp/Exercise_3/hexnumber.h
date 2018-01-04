#ifndef HEXNUMBER_H
#define HEXNUMBER_H
#include "number.h"

class HexNumber : public Number
{
public:
    explicit HexNumber(int value);
    virtual void printIt() const override;
};

#endif // HEXNUMBER_H
