#include <QCoreApplication>
#include <iostream>
#include "hybridharddrive.h"
using std::cout;
using std::endl;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    HybridHardDrive storage{};
    // getId is belongs to both HardDiskDrive and SolidStateDrive
    // The compiler will get an ambiguos error if you not use "vitual" inheritance
    cout << storage.getId();
    return 0;
    return a.exec();
}
