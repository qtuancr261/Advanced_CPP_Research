#include "vehicle.h"

GoAlgorithm Vehicle::getGoAlgorithm() const
{
    return goAlgorithm;
}

void Vehicle::setGoAlgorithm(const GoAlgorithm &value)
{
    goAlgorithm = value;
}

void Vehicle::go() const
{
    goAlgorithm.go();
}

Vehicle::Vehicle()
{

}
