#ifndef OCTNUMBER_H
#define OCTNUMBER_H
#include "number.h"

class OctNumber : public Number
{
public:
    explicit OctNumber(int value);
    virtual void printIt() const override;
};

#endif // OCTNUMBER_H
