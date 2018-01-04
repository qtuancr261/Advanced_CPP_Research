
#include <thread>
#include "keyboardrecorder.h"
#include "thread_guard.h"
using std::thread;
void oops()
{
    int recorderNum{5};

    //----------------------------------------
    KeyboardRecorder Krecoder{recorderNum};
    thread inputThread{Krecoder};

    Thread_Guard threadGuard{inputThread, ThreadType::NonDaemonThread};
    //inputThread.join();
    //inputThread.join();
}
int main(int argc, char *argv[])
{
    oops();
    return 0;
}
