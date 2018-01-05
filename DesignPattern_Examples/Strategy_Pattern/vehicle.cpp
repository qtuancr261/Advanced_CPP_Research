#include "vehicle.h"

const GoStrategy *Vehicle::getGoStrategy() const
{
    return goStrategy;
}

void Vehicle::setGoStrategy(GoStrategy *value)
{
    // Release memory for the past strategy
    delete goStrategy;
    goStrategy = value;
}

void Vehicle::go() const
{
    goStrategy->go();
}

Vehicle::~Vehicle()
{
    // Release memory
    cout << "Release memory" << endl;
    delete goStrategy;
}

Vehicle::Vehicle() : goStrategy{nullptr}
{

}
