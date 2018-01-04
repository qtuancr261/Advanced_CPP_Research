#include "point.h"

double Point::getX() const
{
    return x;
}

void Point::setX(double value)
{
    x = value;
}

double Point::getY() const
{
    return y;
}

void Point::setY(double value)
{
    y = value;
}

Point::Point(double xValue, double yValue)
    : x{xValue}, y{yValue}
{
    // Default constructor
}
