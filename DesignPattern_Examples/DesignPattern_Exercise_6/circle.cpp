#include "circle.h"

Circle::Circle() : Shape{}, radius{0}
{

}

void Circle::inputData()
{
    cout << "-----CIRCLE DATA-----" << endl;
    cout << "Input radius value: ";
    cin >> radius;
}

void Circle::outputData() const
{
    cout << ">CIRCLE | ";
    cout << "Radius value: " << radius << endl;
}

double Circle::area() const
{
    return PI * radius * radius;
}

void Circle::justTest()
{
    cout << "CIRCLE" << endl;
}
