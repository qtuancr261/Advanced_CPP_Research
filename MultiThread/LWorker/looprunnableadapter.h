#ifndef LOOPRUNNABLEADAPTER_H
#define LOOPRUNNABLEADAPTER_H
#include <cassert>
#include "looprunnable.h"
template <typename CBObject>
class LoopRunnableAdapter : public LoopRunnable {
public:
    using CallBack = void (CBObject::*)(void* sender);

private:
    LoopRunnableAdapter() = default;
    CBObject* _pObj;
    CallBack _method;

public:
    LoopRunnableAdapter(const std::string& name, CBObject* cbObj, CallBack method)
        : _pObj{cbObj}
        , _method{method}
        , LoopRunnable(name) {
        assert(_pObj != nullptr);
    }

    LoopRunnableAdapter(const std::string& name, CBObject& cbObj, CallBack method)
        : _pObj{&cbObj}
        , _method{method}
        , LoopRunnable(name) {
        assert(_pObj != nullptr);
    }

    LoopRunnableAdapter(const LoopRunnableAdapter& srcAdapter) = default;

    ~LoopRunnable() = default;

public:
    LoopRunnable& operator=(const LoopRunnableAdapter& srcAdapter) = default;

    void runOne() override { (_pObj->*_method)(this); }
};

#endif	// LOOPRUNNABLEADAPTER_H
