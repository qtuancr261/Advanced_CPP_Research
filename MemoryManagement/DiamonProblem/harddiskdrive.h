#ifndef HARDDISKDRIVE_H
#define HARDDISKDRIVE_H
#include "storagedevice.h"

class HardDiskDrive : public virtual StorageDevice
{
public:
    explicit HardDiskDrive(int id = 0, string name = "device");
};

#endif // HARDDISKDRIVE_H
