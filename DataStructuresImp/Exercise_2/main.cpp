#include "pet.h"
#include "dog.h"
#include "fish.h"
int main(int argc, char *argv[])
{
    Dog mimi{"Mimi"};
    mimi.say();
    Fish nemo{"Nemo"};
    nemo.say();
    return 0;
}
