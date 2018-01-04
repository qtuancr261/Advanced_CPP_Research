#include "equitriangle.h"

EquiTriangle::EquiTriangle(double edge) : Shape(edge)
{

}

double EquiTriangle::area() const
{
    return 0.5 * demensionValue * (demensionValue * sin(60.0 * PI / 180.0));
}
