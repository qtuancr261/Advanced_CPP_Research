#ifndef WORKABLE_H
#define WORKABLE_H
#include <mutex>
#include "looprunnableadapter.h"
class Workable : public LoopRunnableAdapter<Workable> {
private:  // type alias declaration
    using LRunnableAdapterType = LoopRunnableAdapter<Workable>;

public:	 // inner type
    class Job : public RunnableIf {};

private:
    int _connSocket;
    std::mutex _connSocketMutex;  // use for Workable only
protected:
    std::mutex _connSocketWrMutex;
    std::mutex _connSocketRdMutex;

public:
    Workable();
};

#endif	// WORKABLE_H
