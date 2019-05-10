#include <iostream>
#include <thread>
using namespace std;
int say() {
    cout << "Hello concurrent world " << endl;
    cout << " ------" << endl;
    return 1;
}
int main() {
    thread worker(say);
    worker.join();
    return 0;
}
