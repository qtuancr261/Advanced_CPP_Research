#ifndef SUBJECT_H
#define SUBJECT_H
#include "../observer/observer.h"
class Subject
{
    virtual void registerObserver(const Observer& newObserver) = 0;
    virtual void removeObserver(const Observer& anObserver) = 0;
    virtual void notifyAllObserver() const = 0;
};
#endif // SUBJECT_H
