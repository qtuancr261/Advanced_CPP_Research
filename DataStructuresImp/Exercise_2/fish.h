#ifndef FISH_H
#define FISH_H
#include "pet.h"
#include <iostream>
using std::cout;
using std::endl;

class Fish : public Pet
{
public:
    explicit Fish(string name);
    virtual void say() const override;
};

#endif // FISH_H
