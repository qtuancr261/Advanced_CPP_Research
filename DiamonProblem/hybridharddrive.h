#ifndef HYBRIDHARDDRIVE_H
#define HYBRIDHARDDRIVE_H
#include "harddiskdrive.h"
#include "solidstatedrive.h"

class HybridHardDrive : public HardDiskDrive, public SolidStateDrive
{
public:
    HybridHardDrive();
};

#endif // HYBRIDHARDDRIVE_H
