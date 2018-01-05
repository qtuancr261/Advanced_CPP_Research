#include "jetfighter.h"

JetFighter::JetFighter()
{
    setGoStrategy(new GoByFlyingFastStrategy());
}
