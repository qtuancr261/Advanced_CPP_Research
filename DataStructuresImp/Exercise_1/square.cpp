#include "square.h"

Square::Square(double edge): Shape(edge)
{

}

double Square::area() const
{
    return demensionValue * demensionValue;
}
