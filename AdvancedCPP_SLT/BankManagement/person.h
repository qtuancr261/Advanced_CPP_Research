#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::string;

class Person
{
private:
    string name;
    int age;
    string address;
    string phoneNumber;
    const string id;
public:
    Person() = default;
    explicit Person(string defName);

    const string& getName() const;
    void setName(string name);

    int getAge() const;
    void setAge(int age);

    const string& getAddress() const;
    void setAddress(string address);

    const string& getPhoneNumber() const;
    void setPhoneNumber(string phoneNumber);
    virtual ~Person();
};

#endif // PERSON_H
