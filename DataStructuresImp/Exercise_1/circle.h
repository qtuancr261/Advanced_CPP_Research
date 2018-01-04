#ifndef CIRCLE_H
#define CIRCLE_H
#include "shape.h"

class Circle : public Shape
{
public:
    Circle() = default;
    explicit Circle(double radius);
    virtual double area() const override;
};

#endif // CIRCLE_H
