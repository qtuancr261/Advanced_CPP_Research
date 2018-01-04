#include "shape.h"

int Shape::getUndoIndex() const
{
    return undoIndex;
}

void Shape::setUndoIndex(int value)
{
    undoIndex = value;
}

ActionEnum Shape::getCurrentAction() const
{
    if (currentAction.empty())
        return ActionEnum::None;
    return currentAction.top();
}

void Shape::removeCurrentAction()
{
    if (!currentAction.empty())
        currentAction.pop();
}

void Shape::setCurrentAction(const ActionEnum &value)
{
    currentAction.push(value);
}

ActionEnum Shape::getCurrentUDAction() const
{
    if (currentUDAction.empty())
        return ActionEnum::None;
    return currentUDAction.top();
}

void Shape::removeCurrentUDAction()
{
    if (!currentUDAction.empty())
        currentUDAction.pop();
}

void Shape::setCurrentUDAction(const ActionEnum &value)
{
    currentUDAction.push(value);
}

Shape::Shape() : centralPoint{}, undoIndex{0}
{
    // default contructor
}

void Shape::justTest()
{
    cout << "Base Shape" << endl;
}
