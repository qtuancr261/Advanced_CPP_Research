#include "cpu.h"

CPU::CPU(Computer* computer) : ComponentDecorator{computer}
{

}

std::string CPU::description() const
{
    cout << "CPU DES CALLED" << endl;
    return computer->description() + " with a cpu";
}

CPU::~CPU()
{
    cout << "CPU DESTRUCTOR" << endl;
}
