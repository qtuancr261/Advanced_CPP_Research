#include "cuboid.h"
Cuboid::Cuboid() : Shape{}, width{}, height{}, length{}
{

}

void Cuboid::inputData()
{
    cout << "-----CUBOID(3D) DATA-----" << endl;
    cout << "Input width value: ";
    cin >> width;
    cout << "Input height value: ";
    cin >> height;
    cout << "Input length value: ";
    cin >> length;
}

void Cuboid::outputData() const
{
    cout << ">CUBOID(3D) | ";
    cout << " Width value: " << width;
    cout << " Height value: " << height;
    cout << " Length value: " << length << endl;
}

double Cuboid::area() const
{
    return 2.0 * (width * height + width * length + height * length);
}
