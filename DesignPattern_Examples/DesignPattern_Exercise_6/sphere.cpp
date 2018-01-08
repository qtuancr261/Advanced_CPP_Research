#include "sphere.h"

Sphere::Sphere() : Shape{}, radius{}
{

}

void Sphere::inputData()
{
    cout << "-----SPHERE(3D) DATA-----" << endl;
    cout << "Input radius value: ";
    cin >> radius;
}

void Sphere::outputData() const
{
    cout << ">CIRCLE | ";
    cout << "Radius value: " << radius << endl;
}

double Sphere::area() const
{
    return 4.0 * PI * radius * radius;
}
