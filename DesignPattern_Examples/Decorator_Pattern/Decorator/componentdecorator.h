#ifndef COMPONENTDECORATOR_H
#define COMPONENTDECORATOR_H
#include "../computer.h"

class ComponentDecorator : public Computer
{
protected:
    Computer* computer;
public:
    ComponentDecorator(Computer* computer);
    virtual string description() const = 0;
    ~ComponentDecorator();
};

#endif // COMPONENTDECORATOR_H
