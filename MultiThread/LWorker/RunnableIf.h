#ifndef RUNNABLEIF_H
#define RUNNABLEIF_H
class RunnableIf {
public:
    RunnableIf() = default;
    virtual ~RunnableIf() = default;

    // thread will do here
    // must be overriden by subclasses
    virtual void run() = 0;
};

#endif  // RUNNABLEIF_H
