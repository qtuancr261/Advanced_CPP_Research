#include "componentdecorator.h"

ComponentDecorator::ComponentDecorator(Computer *computer)
    : computer{computer}
{
    cout << "Decorator constructor" << endl;
}

ComponentDecorator::~ComponentDecorator()
{
    cout << "COMPONENT DECORATOR DESTRUCTOR" << endl;
    delete computer;
}
