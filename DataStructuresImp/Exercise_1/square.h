#ifndef SQUARE_H
#define SQUARE_H
#include "shape.h"

class Square : public Shape
{
public:
    Square() = default;
    explicit Square(double edge);
    virtual double area() const override;
};

#endif // SQUARE_H
