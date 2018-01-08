#ifndef SHAPE2DFACTORY_H
#define SHAPE2DFACTORY_H
#include "shapefactory.h"
#include "../rectangle.h"
#include "../circle.h"
class Shape2DFactory : public ShapeFactory
{
public:
    virtual Shape* createStraightShape() override;
    virtual Shape* createCurvedShape() override;

};

#endif // SHAPE2DFACTORY_H
