#include <QCoreApplication>
#include "subject/weatherdata.h"
#include "observer/currentconditionsdisplay.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    shared_ptr<WeatherData> weatherData{make_shared<WeatherData>()};
    shared_ptr<CurrentConditionsDisplay> display1{make_shared<CurrentConditionsDisplay>()};
    shared_ptr<CurrentConditionsDisplay> display2{make_shared<CurrentConditionsDisplay>()};
    shared_ptr<CurrentConditionsDisplay> display3{make_shared<CurrentConditionsDisplay>()};
    display1->setSubject(weatherData);
    display2->setSubject(weatherData);
    weatherData->setMeasurements(27.0, 100, 68);
    weatherData->removeObserver(display2);
    weatherData->setMeasurements(28.3, 100, 65);
    return 0;
    return a.exec();
}
