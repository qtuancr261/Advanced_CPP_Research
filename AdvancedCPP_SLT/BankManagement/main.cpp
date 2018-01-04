#include <iostream>
#include "person.h"
using std::cout;
using std::endl;
int main(int argc, char *argv[])
{
    for (int i{}; i < argc; i++)
        cout << argv[i] << " " << endl;
    Person* peter{new Person("Peter")};
    return 0;
}
