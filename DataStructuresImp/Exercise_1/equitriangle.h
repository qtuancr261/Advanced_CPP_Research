#ifndef EQUITRIANGLE_H
#define EQUITRIANGLE_H
#include "shape.h"
using std::sin;
class EquiTriangle : public Shape
{
public:
    EquiTriangle() = default;
    EquiTriangle(double edge);
    virtual double area() const override;
};

#endif // EQUITRIANGLE_H
