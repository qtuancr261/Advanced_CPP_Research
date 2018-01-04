#ifndef THREAD_GUARD_H
#define THREAD_GUARD_H
#include <thread>
#include "enumerators.h"
using std::thread;

class Thread_Guard
{
private:
    thread& gThread; // guarded Thread
    ThreadType gType;
public:
    explicit Thread_Guard(thread& gThread, ThreadType type);
    Thread_Guard(const thread& thread) = delete;
    Thread_Guard& operator=(const thread& thread) = delete;
    virtual ~Thread_Guard();
};

#endif // THREAD_GUARD_H
