#ifndef GOBYDRIVEALGORITHM_H
#define GOBYDRIVEALGORITHM_H
#include "gostrategy.h"

class GoByDriveStrategy : public GoStrategy
{
public:
    GoByDriveStrategy() = default;
    void go() const;
};

#endif // GOBYDRIVEALGORITHM_H
