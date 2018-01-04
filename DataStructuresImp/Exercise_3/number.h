#ifndef NUMBER_H
#define NUMBER_H
#include <iostream>
using std::cout;
using std::endl;
using std::dec;
using std::oct;
using std::hex;
class Number
{
protected:
    int value;
public:
    explicit Number(int value);
    virtual void printIt() const = 0;
    virtual ~Number() = default;
};

#endif // NUMBER_H
