#ifndef DISPLAYELEMENT_H
#define DISPLAYELEMENT_H
class DisplayElement
{
    virtual void display(double temperature, double humidity, double pressure) const = 0;
};
#endif // DISPLAYELEMENT_H
