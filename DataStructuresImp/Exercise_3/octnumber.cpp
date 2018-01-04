#include "octnumber.h"

OctNumber::OctNumber(int value) : Number(value)
{

}

void OctNumber::printIt() const
{
    cout << oct << value << endl;
}
