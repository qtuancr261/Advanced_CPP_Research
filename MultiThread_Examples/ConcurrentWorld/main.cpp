#include <iostream>
#include <thread>
#include "threadguard.h"
#include "worker.h"
using namespace std;
struct funct {
    int& _refI;
    funct(int& refI) : _refI{refI} {
        // init
    }

    void operator()() const {
        for (int var = 0; var < _refI; ++var) {
            cout << var << " -> " << _refI << endl;
        }
    }

    bool doTheSameThingAsFunctor() {
        for (int var = 0; var < 5; ++var) {
            cout << var << " -> " << 5 << endl;
        }
        return true;
    }
};
int say(string& message) {
    cout << message << endl;
    cout << " ------" << endl;
    message.append(" - said");
    cout << "Internal thread we say after appending: " << message << endl;
    return 1;
}
void sayHi() { cout << "Hi " << endl; }
int main() {
    int i = 20;
    funct F1{i};
    // std::thread works with any callable type
    // pass a function
    thread thread_1{sayHi};
    thread_1.join();

    // so we could pass an instance of a class with a function call operator to the std::thread
    thread thread_2{F1};
    thread_2.join();

    // Or use the functor directly
    thread thread_3{funct(i)};
    thread_3.join();

    //
    thread thread_4{&funct::doTheSameThingAsFunctor, &F1};
    thread_4.join();

    string message{"Hello"};
    // By default the arguments are copied into internal storage
    // Where they can be access by the newly created thread of execution
    // Even if the corresponding parameter in the function is expecting a ref
    // So that you need to wrap the arguments that really need to be ref in std::ref()
    thread thread_5{say, std::ref(message)};
    thread_5.join();
    cout << "outside the thread we say after appending: " << message << endl;

    thread thread_6{Worker(1)};
    thread_6.join();
    return 0;
}
