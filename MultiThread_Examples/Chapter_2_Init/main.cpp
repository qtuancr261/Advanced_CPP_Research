#include <iostream>
#include <thread>
#include <vector>
#include <exception>
#include <threadguard.h>
using std::cout;
using std::endl;
using std::thread;
using std::vector;
using std::exception;
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
    //cout << (thread_tmp.joinable() ? "Be advised" : " Alreay joined or detached ") << endl;
}
int main(int argc, char *argv[])
{
    justDoSomething();
    cout << "stop doing stupid things" << endl;
    return 0;
}
