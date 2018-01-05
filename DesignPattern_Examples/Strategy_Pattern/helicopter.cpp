#include "helicopter.h"

Helicopter::Helicopter()
{
    setGoStrategy(new GoByFlyingStrategy);
}
