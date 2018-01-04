#include "circle.h"

Circle::Circle(double radius) : Shape(radius)
{

}

double Circle::area() const
{
    return demensionValue * demensionValue * PI;
}
