
#include <iostream>
#include "circle.h"
#include "equitriangle.h"
#include "square.h"
using std::cout;
using std::endl;
int main(int argc, char *argv[])
{
    Circle circleA{20};
    cout << "circleA: " << circleA.area() << endl;
    EquiTriangle eTriangleA{20};
    cout << "eTriangleA: " << eTriangleA.area() << endl;
    Square squareA{10};
    cout << "squareA: " << squareA.area() << endl;
    return 0;
}
