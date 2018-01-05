#ifndef GOBYFLYINGFASTALGORITHM_H
#define GOBYFLYINGFASTALGORITHM_H
#include "gostrategy.h"

class GoByFlyingFastStrategy : public GoStrategy
{
public:
    GoByFlyingFastStrategy() = default;
    void go() const;
};

#endif // GOBYFLYINGFASTALGORITHM_H
