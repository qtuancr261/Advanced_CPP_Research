#ifndef WEATHERDATA_H
#define WEATHERDATA_H
#include "subject.h"
#include "list"
#include "vector"
using std::list;
using std::vector;
class WeatherData : public Subject
{
private:
    list<ObserverPtr> observers;
    double temperature;
    double pressure;
    double humidity;
public:
    WeatherData();
    virtual void registerObserver(const ObserverPtr& newObserver) override;
    virtual void removeObserver(const ObserverPtr& anObserver) override;
    virtual void notifyAllObservers() const override;
    void measurementsChanged();
};

#endif // WEATHERDATA_H
