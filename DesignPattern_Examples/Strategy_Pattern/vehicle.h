#ifndef VEHICLE_H
#define VEHICLE_H
#include "strategy/gobydrivestrategy.h"
#include "strategy/gobyflyingstrategy.h"
#include "strategy/gobyflyingfaststrategy.h"
class Vehicle
{
private:
    // "has a" relationship instead of "is a" relationship
    GoStrategy* goStrategy;
public:
    Vehicle();
    const GoStrategy* getGoStrategy() const;
    void setGoStrategy(GoStrategy *value);
    void go() const;
    virtual ~Vehicle();
};

#endif // VEHICLE_H
