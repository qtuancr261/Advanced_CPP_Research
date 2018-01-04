#ifndef POINT_H
#define POINT_H


class Point
{
private:
    double x;
    double y;
public:
    explicit Point(double xValue = 0.0, double yValue = 0.0);

    double getX() const;
    void setX(double value);

    double getY() const;
    void setY(double value);
};

#endif // POINT_H
