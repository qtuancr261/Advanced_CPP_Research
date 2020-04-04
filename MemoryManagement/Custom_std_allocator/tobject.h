#ifndef TOBJECT_H
#define TOBJECT_H
#include <string>
#include <iostream>
using std::string;
class TObject
{
private:
    int id;
    string ip;
public:
    TObject();
    void* operator new(size_t size);
};

#endif // TOBJECT_H
