#ifndef CUBOID_H
#define CUBOID_H
#include "shape.h"

class Cuboid : public Shape
{
private:
    double width;
    double height;
    double length;
public:
    Cuboid();
    virtual void inputData() override;
    virtual void outputData() const override;
    virtual double area() const override;

};

#endif // CUBOID_H
