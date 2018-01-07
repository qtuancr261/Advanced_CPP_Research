#ifndef CPU_H
#define CPU_H
#include "componentdecorator.h"

class CPU : public ComponentDecorator
{
public:
    explicit CPU(Computer *computer);
    virtual string description() const final;
    ~CPU();
};

#endif // CPU_H
