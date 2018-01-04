#include "fish.h"

Fish::Fish(std::string name) : Pet(name)
{

}

void Fish::say() const
{
    cout << name << " said: " << "________" << endl;
}
