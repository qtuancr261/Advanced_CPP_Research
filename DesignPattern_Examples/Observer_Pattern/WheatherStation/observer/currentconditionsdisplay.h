#ifndef CURRENTCONDITIONSDISPLAY_H
#define CURRENTCONDITIONSDISPLAY_H
#include "observer.h"
#include "displayelement.h"
#include "../subject/subject.h"
using std::weak_ptr;
using std::enable_shared_from_this;
class CurrentConditionsDisplay : public Observer, public DisplayElement, public enable_shared_from_this<CurrentConditionsDisplay>
{
private:
    double temperature;
    double humidity;
    double pressure;
    weak_ptr<Subject> weatherData;
public:
    CurrentConditionsDisplay();
    void setSubject(const shared_ptr<Subject>& weatherData);
    // DisplayElement interface
public:
    virtual void display() const override;

    // Observer interface
public:
    virtual void update(double temperature, double humidity, double pressure) override;
    virtual ~CurrentConditionsDisplay();
};

#endif // CURRENTCONDITIONSDISPLAY_H
