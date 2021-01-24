#include "hybridharddrive.h"

HybridHardDrive::HybridHardDrive(int id, std::string name)
    : StorageDevice{id, name}, HardDiskDrive{}, SolidStateDrive{}
{

}
