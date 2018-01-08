#ifndef SHAPE3DFACTORY_H
#define SHAPE3DFACTORY_H
#include "shapefactory.h"

class Shape3DFactory : public ShapeFactory
{
public:
    virtual Shape* createStraightShape() override;
    virtual Shape* createCurvedShape() override;
};

#endif // SHAPE3DFACTORY_H
