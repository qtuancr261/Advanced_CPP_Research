#include "pekinduck.h"

PekinDuck::PekinDuck()
    : Duck{new FlyWithWings, new QuackQuack}
{
    // default constructor
}
