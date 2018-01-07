#ifndef COMPUTER_H
#define COMPUTER_H
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
class Computer
{
public:
    Computer();
    virtual std::string description() const;
    virtual ~Computer() = default;

};

#endif // COMPUTER_H
