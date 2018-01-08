#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "shape.h"

class Rectangle : public Shape
{
private:
    double width;
    double height;
public:
    Rectangle();
    virtual void inputData() override;
    virtual void outputData() const override;
    virtual double area() const override;
};

#endif // RECTANGLE_H
