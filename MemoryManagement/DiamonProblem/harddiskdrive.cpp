#include "harddiskdrive.h"

HardDiskDrive::HardDiskDrive(int id, std::string name)
    : StorageDevice{id, name}
{
    qDebug() << "HardDiskDrive Constructor";
}
