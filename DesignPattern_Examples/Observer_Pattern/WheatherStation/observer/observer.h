#ifndef OBSERVER_H
#define OBSERVER_H
class Observer
{
    virtual void update(double temperature, double humidity, double pressure) = 0;
};
#endif // OBSERVER_H
