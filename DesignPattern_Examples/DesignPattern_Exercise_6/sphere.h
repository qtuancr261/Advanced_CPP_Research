#ifndef SPHERE_H
#define SPHERE_H
#include "shape.h"

class Sphere : public Shape
{
private:
    double radius;
public:
    Sphere();
    virtual void inputData() override;
    virtual void outputData() const override;
    virtual double area() const override;
};

#endif // SPHERE_H
