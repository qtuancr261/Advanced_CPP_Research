#ifndef SHAPE_H
#define SHAPE_H
#include <cmath>
const double PI = 3.14;
class Shape
{
protected:
    double demensionValue;
public:
    Shape() = default;
    explicit Shape(double demensionValue);
    double getDemensionValue() const;
    void setDemensionValue(double demensionValue);
    virtual double area() const = 0;
    virtual ~Shape() = default;
};

#endif // SHAPE_H
