#ifndef SHAPE2DFACTORY_H
#define SHAPE2DFACTORY_H
#include "shapefactory.h"

class Shape2DFactory : public ShapeFactory
{
public:
    enum class TypeEnum
    {
        Rectangle = 1,
        Circle
    };
    virtual Shape* createShape(int type) override;

};

#endif // SHAPE2DFACTORY_H
