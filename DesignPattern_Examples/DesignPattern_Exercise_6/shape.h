#ifndef SHAPE_H
#define SHAPE_H
#include "point.h"
#include <iostream>
#include <stack>
#include <string>
#include "actionenum.h"
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::stack;
using std::string;
const double PI{3.14};
class Shape
{
protected:
    Point centralPoint;
    int undoIndex;
    stack<ActionEnum> currentAction;
    stack<ActionEnum> currentUDAction;
public:
    Shape();
    virtual void inputData() = 0;
    virtual void outputData() const = 0;
    virtual double area() const = 0;
    virtual ~Shape() = default;

    int getUndoIndex() const;
    void setUndoIndex(int value);

    ActionEnum getCurrentAction() const;
    void removeCurrentAction();
    void setCurrentAction(const ActionEnum &value);
    ActionEnum getCurrentUDAction() const;
    void removeCurrentUDAction();
    void setCurrentUDAction(const ActionEnum &value);
};

#endif // SHAPE_H
