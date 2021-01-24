#include "solidstatedrive.h"

SolidStateDrive::SolidStateDrive(int id, std::string name)
    : StorageDevice{id, name}
{
    qDebug() << "SolidStateDrive constructor";
}
