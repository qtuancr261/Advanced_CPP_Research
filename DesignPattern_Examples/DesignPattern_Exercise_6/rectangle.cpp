#include "rectangle.h"

Rectangle::Rectangle() : Shape{}, width{0}, height{0}
{

}

void Rectangle::inputData()
{
    cout << "-----RECT DATA-----" << endl;
    cout << "Input width value: ";
    cin >> width;
    cout << "Input height value: ";
    cin >> height;
}

void Rectangle::outputData() const
{
    cout << ">RECT | ";
    cout << " Width value: " << width;
    cout << " Height value: " << height << endl;
}

double Rectangle::area() const
{
    return width * height;
}

