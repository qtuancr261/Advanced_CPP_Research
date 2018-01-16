#ifndef FLYBEHAVIOR_H
#define FLYBEHAVIOR_H
#include <string>
using std::string;
class FlyBehavior
{
public:
    virtual string fly() const = 0;
    virtual ~FlyBehavior() = default;
};
#endif // FLYBEHAVIOR_H
