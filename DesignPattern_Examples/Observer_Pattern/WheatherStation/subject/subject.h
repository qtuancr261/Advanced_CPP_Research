#ifndef SUBJECT_H
#define SUBJECT_H
#include "../observer/observer.h"
#include <memory>
using std::shared_ptr;
using std::make_shared;
using ObserverPtr = shared_ptr<Observer>;
class Subject
{
public:
    virtual void registerObserver(const ObserverPtr& newObserver) = 0;
    virtual void removeObserver(const ObserverPtr& anObserver) = 0;
    virtual void notifyAllObserver() const = 0;
};
#endif // SUBJECT_H
