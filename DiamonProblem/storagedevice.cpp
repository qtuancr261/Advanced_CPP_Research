#include "storagedevice.h"

StorageDevice::StorageDevice(int id, std::string name)
    : id{id}, name{name}
{
    qDebug() << "StorageDevide Constructor";
}

int StorageDevice::getId() const
{
    return id;
}

void StorageDevice::setId(int value)
{
    id = value;
}

string StorageDevice::getName() const
{
    return name;
}

void StorageDevice::setName(const string &value)
{
    name = value;
}



