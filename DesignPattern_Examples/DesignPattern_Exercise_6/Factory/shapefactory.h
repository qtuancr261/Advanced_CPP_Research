#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H
#include "../shape.h"
class ShapeFactory
{
public:
    virtual Shape* createShape(int type) = 0;
};
#endif // SHAPEFACTORY_H
