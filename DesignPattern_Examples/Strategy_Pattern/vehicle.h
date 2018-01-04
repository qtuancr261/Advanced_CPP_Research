#ifndef VEHICLE_H
#define VEHICLE_H
#include "goalgorithm.h"

class Vehicle
{
private:
    GoAlgorithm goAlgorithm;
public:
    Vehicle();
    GoAlgorithm getGoAlgorithm() const;
    void setGoAlgorithm(const GoAlgorithm &value);
    void go() const;
};

#endif // VEHICLE_H
