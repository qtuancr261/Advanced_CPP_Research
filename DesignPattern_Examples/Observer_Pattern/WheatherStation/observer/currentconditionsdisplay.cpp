#include "currentconditionsdisplay.h"

CurrentConditionsDisplay::CurrentConditionsDisplay()
    : temperature{}, humidity{}, pressure{}, weatherData{}
{

}

void CurrentConditionsDisplay::setSubject(const shared_ptr<Subject> &weatherData)
{
    weatherData->registerObserver(shared_from_this());
    this->weatherData = weatherData;
}


void CurrentConditionsDisplay::display() const
{
    cout << "Current Conditions : ";
    cout << setw(10) << "Temp: " << setw(4) << temperature << " C Degrees" <<endl;
    cout << setw(10) << "Humidity: " << setw(4) << humidity << " %" <<endl;
    cout << setw(10) << "Pressure: " << setw(4) << pressure << endl;
}

void CurrentConditionsDisplay::update(double temperature, double humidity, double pressure)
{
    this->temperature = temperature;
    this->humidity = humidity;
    this->pressure = pressure;
    display();
}

CurrentConditionsDisplay::~CurrentConditionsDisplay()
{
    qDebug() << "Display has been deleted";
}
