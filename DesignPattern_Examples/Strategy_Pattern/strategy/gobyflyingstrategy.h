#ifndef GOBYFLYINGALGORITHM_H
#define GOBYFLYINGALGORITHM_H
#include "gostrategy.h"

class GoByFlyingStrategy : public GoStrategy
{
public:
    GoByFlyingStrategy();
    void go() const;
};

#endif // GOBYFLYINGALGORITHM_H
