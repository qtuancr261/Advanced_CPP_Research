#ifndef HYBRIDHARDDRIVE_H
#define HYBRIDHARDDRIVE_H
#include "harddiskdrive.h"
#include "solidstatedrive.h"

class HybridHardDrive : public HardDiskDrive, public SolidStateDrive
{
public:
    explicit HybridHardDrive(int id = 0, string name = "device");
};

#endif // HYBRIDHARDDRIVE_H
