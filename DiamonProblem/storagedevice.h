#ifndef STORAGEDEVICE_H
#define STORAGEDEVICE_H
#include <string>
using std::string;
class StorageDevice
{
    int id;
    string name;
public:
    explicit StorageDevice(int id = 0, string name = "device");
    virtual ~StorageDevice() = default;
    int getId() const;
    void setId(int value);
    string getName() const;
    void setName(const string &value);
};

#endif // STORAGEDEVICE_H
