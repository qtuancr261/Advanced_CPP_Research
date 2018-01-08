#ifndef SHAPEFACTORY_H
#define SHAPEFACTORY_H
#include "../shape.h"
class ShapeFactory
{
public:
    virtual Shape* createStraightShape() = 0;
    virtual Shape* createCurvedShape() = 0;
    virtual ~ShapeFactory() = default;
};
#endif // SHAPEFACTORY_H
