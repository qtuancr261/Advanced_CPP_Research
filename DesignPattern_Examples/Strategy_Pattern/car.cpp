#include "car.h"

Car::Car()
{
    setGoStrategy(new GoByDriveStrategy{});
}
