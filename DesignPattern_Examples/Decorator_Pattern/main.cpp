#include "Decorator/componentdecorator.h"
#include "Decorator/cpu.h"
#include "Decorator/gpu.h"
int main(int argc, char *argv[])
{
    Computer* myPC{new Computer{}};
    myPC = new CPU{myPC};
    myPC = new GPU{myPC};
    cout << myPC->description() << endl;
    delete myPC;
    return 0;
}
