#include "person.h"
Person::Person(std::string defName)
    : name{defName}, age{18}, address{}, phoneNumber{}, id{"GTK"}
{
    cout << "Person constructor" << endl;
}

const std::string &Person::getName() const
{
    return this->name;
}

void Person::setName(std::string name)
{
    this->name = name;
}

int Person::getAge() const
{
    return this->age;
}

void Person::setAge(int age)
{
    this->age = age;
}

const std::string &Person::getAddress() const
{
    return this->address;
}

void Person::setAddress(std::string address)
{
    this->address = address;
}

const std::string &Person::getPhoneNumber() const
{
    return this->phoneNumber;
}

void Person::setPhoneNumber(std::string phoneNumber)
{
    this->phoneNumber = phoneNumber;
}

Person::~Person()
{
    cout << "Person destructor" << endl;
}

