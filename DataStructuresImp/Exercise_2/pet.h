#ifndef PET_H
#define PET_H
#include <string>
using std::string;
class Pet
{
protected:
    string name;
public:
    explicit Pet(string name);
    virtual void say() const = 0;
    virtual ~Pet() = default;
};

#endif // PET_H
