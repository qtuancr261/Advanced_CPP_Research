#include "dog.h"

Dog::Dog(std::string name) : Pet(name)
{

}

void Dog::say() const
{
    cout << name << " said: oop_oop" << endl;
}
