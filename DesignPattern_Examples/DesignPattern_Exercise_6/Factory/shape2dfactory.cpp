#include "shape2dfactory.h"
Shape *Shape2DFactory::createStraightShape()
{
    Shape* newShape{new Rectangle};
    newShape->inputData();
    return newShape;
}

Shape *Shape2DFactory::createCurvedShape()
{
    Shape* newShape{new Circle};
    newShape->inputData();
    return newShape;
}
