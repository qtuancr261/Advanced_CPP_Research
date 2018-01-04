#include "shape.h"

Shape::Shape(double demensionValue) : demensionValue{demensionValue}
{

}

double Shape::getDemensionValue() const
{
    return demensionValue;
}

void Shape::setDemensionValue(double demensionValue)
{
    this->demensionValue = demensionValue;
}
