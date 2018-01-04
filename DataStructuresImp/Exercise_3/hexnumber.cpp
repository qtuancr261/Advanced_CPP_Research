#include "hexnumber.h"
HexNumber::HexNumber(int value) : Number(value)
{

}

void HexNumber::printIt() const
{
    cout << hex << value << endl;
}
