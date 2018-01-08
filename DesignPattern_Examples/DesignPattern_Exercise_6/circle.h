#ifndef CIRCLE_H
#define CIRCLE_H
#include "shape.h"

class Circle : public Shape
{
private:
    double radius;
public:
    Circle();
    virtual void inputData() override;
    virtual void outputData() const override;
    virtual double area() const override;
};

#endif // CIRCLE_H
