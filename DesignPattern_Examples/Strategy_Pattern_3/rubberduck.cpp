#include "rubberduck.h"

RubberDuck::RubberDuck()
    : Duck{new FlyInDream, new MuteQuack}
{
    // default constructor
}
