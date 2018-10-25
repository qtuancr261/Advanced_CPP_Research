#ifndef WEATHERDATA_H
#define WEATHERDATA_H
#include "subject.h"
#include <list>
#include <vector>
#include <QtDebug>
using std::list;
using std::vector;
class WeatherData : public Subject
{
    Q_OBJECT
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
    virtual ~WeatherData();
signals:
    void measurementsChanged();

public:
    void setMeasurements(double temperature, double pressure, double humidity);
};

#endif // WEATHERDATA_H
