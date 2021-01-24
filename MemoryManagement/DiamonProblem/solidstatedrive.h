#ifndef SOLIDSTATEDRIVE_H
#define SOLIDSTATEDRIVE_H
#include "storagedevice.h"

class SolidStateDrive : public virtual StorageDevice
{
public:
    SolidStateDrive(int id = 0, string name = "device");
};

#endif // SOLIDSTATEDRIVE_H
