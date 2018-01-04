#include "thread_guard.h"
#include <thread>
Thread_Guard::Thread_Guard(std::thread &gThread, ThreadType type) : gThread{gThread}, gType{type}
{

}

Thread_Guard::~Thread_Guard()
{
    // Make sure GThread is finished
    if (gThread.joinable())
    {
        if (gType == ThreadType::DaemonThread)
            gThread.detach();
        else
            gThread.join();
    }

}
