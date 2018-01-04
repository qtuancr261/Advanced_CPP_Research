#ifndef KEYBOARDRECODER_H
#define KEYBOARDRECODER_H
#include <thread>
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::getline;
using std::endl;
using std::string;

class KeyboardRecorder
{
private:
    int& refValue;
public:
    KeyboardRecorder(int& refValue);
    void operator() () const;
};

#endif // KEYBOARDRECODER_H
