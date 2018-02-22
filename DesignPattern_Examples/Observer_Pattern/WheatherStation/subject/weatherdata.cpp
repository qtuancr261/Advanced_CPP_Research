#include "weatherdata.h"

WeatherData::WeatherData()
{
    QObject::connect(this, &WeatherData::measurementsChanged, this, &WeatherData::notifyAllObservers);
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
    qDebug() << "signal - slot";
    for (auto& observer : observers)
    {
        observer->update(temperature, humidity, pressure);
    }
}

WeatherData::~WeatherData()
{
    qDebug() << "WeatherData has been deleted ";
}

void WeatherData::setMeasurements(double temperature, double pressure, double humidity)
{
    this->temperature = temperature;
    this->pressure = pressure;
    this->humidity = humidity;
    emit measurementsChanged();
}
