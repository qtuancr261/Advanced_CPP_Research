#include <iostream>
#include <string>
#include <numeric>
#include "ftemplate.h"
#include "list.h"
#include "stack.h"
using std::string;
// for testing template only
void test(int a)
{
    cout << a;
}
int main(int argc, char *argv[])
{
    stack<string> sqlStatement;
    sqlStatement.push("Unity DE");
    sqlStatement.push("KDE");
    sqlStatement.push("Cinnamon");
    for (int i{}; i < sqlStatement.size(); i++)
        cout << sqlStatement.at(i) << " -> ";
    cout << sqlStatement.first() << " | " << sqlStatement.last() << endl;
    /*int arrayA[]{100, 360, 40, -150, 15};
    cout << std::accumulate(std::begin(arrayA), std::end(arrayA), 0) << endl;
    void (*ptrFunct)(int) = test;
    ptrFunct(450);*/

    return 0;
}
