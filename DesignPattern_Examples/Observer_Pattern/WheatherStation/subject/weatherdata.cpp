#include "weatherdata.h"

WeatherData::WeatherData()
{

}

void WeatherData::registerObserver(const ObserverPtr& newObserver)
{
    observers.push_back(newObserver);
}

void WeatherData::removeObserver(const ObserverPtr& anObserver)
{
    observers.remove(anObserver);
}

void WeatherData::notifyAllObservers() const
{
    for (auto& observer : observers)
    {
        observer->update(temperature, humidity, pressure);
    }
}
