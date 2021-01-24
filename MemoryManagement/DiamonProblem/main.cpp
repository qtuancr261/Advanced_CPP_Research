#include <iostream>
#include "hybridharddrive.h"
using std::cout;
using std::endl;
int main(int argc, char *argv[])
{
    HybridHardDrive storage{};
    // getId is belongs to both HardDiskDrive and SolidStateDrive
    // The compiler will get an ambiguos error if you not use "vitual" inheritance
    cout << storage.getId();

    //SolidStateDrive ssd{};
    return 0;
}
