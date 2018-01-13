#include <iostream>
#include "rubberduck.h"
#include "pekinduck.h"
#include "behavior/flybyrocket.h"
using namespace std;
int main(int argc, char *argv[])
{
    for (int i{}; i < argc;i++)
        cout << argv[i] << endl;
    RubberDuck myGirl;
    cout << myGirl.doFly() << endl;
    cout << myGirl.doQuack() << endl;
    PekinDuck hisGirl;
    cout << hisGirl.doFly() << endl;
    hisGirl.setFlyBehavior(new FlyByRocket);
    cout << hisGirl.doFly() << endl;
    cout << hisGirl.doQuack() << endl;
    return 0;
}
