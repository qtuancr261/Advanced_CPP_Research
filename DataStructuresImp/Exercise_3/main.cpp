#include "decnumber.h"
#include "hexnumber.h"
#include "octnumber.h"
int main(int argc, char *argv[])
{
    DecNumber numA{20};
    numA.printIt();
    HexNumber numB{20};
    numB.printIt();
    OctNumber numC{20};
    numC.printIt();
    return 0;
}
