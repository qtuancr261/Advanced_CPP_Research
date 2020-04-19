/*
 * Author: tuantq3
 * File: main.cpp
 *
 * Created on 16/4/2020
 */
#include <iostream>

void testFunct(char (&a)[10]) { std::cout << typeid(a).name(); }
using namespace std;

int main() {
    cout << "Hello World!" << endl;
    char a10[10]{};
    testFunct(a10);
    return 0;
}
