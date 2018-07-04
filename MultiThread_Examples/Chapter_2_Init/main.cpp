#include <iostream>
#include <thread>
#include <vector>
#include <exception>
#include <string>
#include <threadguard.h>
using std::cout;
using std::endl;
using std::thread;
using std::vector;
using std::exception;
using std::string;
using std::ref;
struct Funct
{
    int num;
    Funct(int& num) : num{num} {}
    void operator() () const
    {
        cout << "Let's start our loop: " <<  endl;
        for (int i{}; i < num; i++)
            cout << i << " -> " << endl;
    }
};
void takeString(int numA, const string& name)
{
    cout << "numA: " << numA << endl;
    cout << "name: " << name << endl;
    //name.append(" KDE Neon");
}
void alterString(string& name)
{
    cout << "name before: " << name;
    name.append(" altered");
}
void justDoSomething()
{
    cout << "Welcome to C++ Concurrency " << endl;
    int i{5};
    Funct funct{i};
    thread thread_tmp{funct};
    ThreadGuard ThreadGuardian{thread_tmp};
    vector<int> vecA{10, 20, 30, 40};
    // use detach() if you dont want to wait for thread_tmp
    // use join() if you want to wait for it
    try
    {
        cout << "vector: ";
        for (int i = 0; i < 10; ++i)
        {
            cout << vecA.at(i) << " - ";
        }
        thread_tmp.join();
    }
    catch(const exception& error)
    {
        cout << "Exception has been catched: " << error.what() << endl;
        //thread_tmp.join();
    }
    //cout << (thread_tmp.joinable() ? "Be advised" : " Already joined or detached ") << endl;
}
void justDoSomeThing_Ver2()
{
    int a{20};
    char bufferName[]{"Thieu Quang Tuan"};
    thread thread_tmp{takeString, a, string(bufferName)};
    //ThreadGuard ThreadGuardian{thread_tmp};
    thread_tmp.detach();
}
void justDoSomeThing_Ver2_1()
{
    int a{25};
    string name{"V3 N3 KD"};
    thread thread_tmp{takeString, a, name};
    thread_tmp.detach();
}
void justAlterString(string& name)
{
    thread thread_tmp{alterString, ref(name)};
    thread_tmp.join();
}
int main(int argc, char *argv[])
{
    // wanna know the main's parameters
    for (int i{}; i < argc; i++)
        cout << argv[i] << endl;
    justDoSomething();
    cout << "stop doing stupid things - 1 " << endl;
    justDoSomeThing_Ver2();
    cout << "stop doing stupid things - 2 " << endl;
    justDoSomeThing_Ver2_1();
    cout << "stop doing stupid things - 3 " << endl;
    //-----------------------------------------------
    string osName{"GNU Linux"};
    justAlterString(osName);
    cout << "stop alterString " << endl;
    cout << osName << endl;
    return 0;
}
