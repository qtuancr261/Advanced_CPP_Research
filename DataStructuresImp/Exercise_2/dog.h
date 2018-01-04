#ifndef DOG_H
#define DOG_H
#include "pet.h"
#include <iostream>
using std::cout;
using std::endl;

class Dog : public Pet
{
public:
    explicit Dog(string name);
    virtual void say() const override;
};

#endif // DOG_H
