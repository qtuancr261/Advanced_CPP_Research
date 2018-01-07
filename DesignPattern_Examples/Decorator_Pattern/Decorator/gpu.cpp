#include "gpu.h"

GPU::GPU(Computer *computer) : ComponentDecorator{computer}
{

}

std::string GPU::description() const
{
    cout << "GPU DES CALLED" << endl;
    return computer->description() + " with a gpu";
}

GPU::~GPU()
{
    cout << "GPU DESTRUCTOR" << endl;
}
