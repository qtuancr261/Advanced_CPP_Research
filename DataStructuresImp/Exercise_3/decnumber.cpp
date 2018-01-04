#include "decnumber.h"

DecNumber::DecNumber(int value) : Number(value)
{

}

void DecNumber::printIt() const
{
    cout << dec << value << endl;
}
