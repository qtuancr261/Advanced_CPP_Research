#include <iostream>
#include <string>
#include <numeric>
#include "qstack.h"
#include "qqueue.h"
using std::string;
// for testing template only
int main(int argc, char *argv[])
{
    qstack<string> stackA{};
    stackA.push("GTK");
    stackA.push("KDE");
    stackA.push("GNOME");
    stackA.push("LXDE");
    while(!stackA.isEmpty())
        cout << stackA.pop() << " ";

    cout << endl;
    qqueue<double> queueA{};
    queueA.insert(10.0);
    queueA.insert(20.0);
    queueA.insert(3.14);
    queueA.insert(5.201);
    while(!queueA.isEmpty())
        cout << queueA.pop() << " ";
    cout << endl;
    return 0;
}
