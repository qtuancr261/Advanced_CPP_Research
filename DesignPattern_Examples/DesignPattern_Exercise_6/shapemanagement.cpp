#include "shapemanagement.h"

ShapeManagement::ShapeManagement()
{

}

ShapeManagement::~ShapeManagement()
{

}

void ShapeManagement::addShape()
{
    int shapeType{0};
    cout << "1. Rectangle.\n";
    cout << "2. Circle.\n";
    cout << "  -> Shape type: ";
    cin >> shapeType;
    switch (shapeType)
    {
    case 1:
    {
        Shape* newShape{new Rectangle{}};
        newShape->inputData();
        // Save index of the new Shape in shapes list
        newShape->setUndoIndex(shapes.size());
        // Save the current action of the new Shape
        newShape->setCurrentAction(ActionEnum::Add);
        shapes.push_back(newShape);
        undoStack.push(newShape);
        // Clear redo stack when beginning a new action
        while(!redoStack.empty())
        {
            redoStack.pop();
        }
        break;
    }
    case 2:
    {
        Shape* newShape{new Circle{}};
        newShape->inputData();
        // Save index of the new Shape in shapes list
        newShape->setUndoIndex(shapes.size());
         // Save the current action of the new Shape
        newShape->setCurrentAction(ActionEnum::Add);
        shapes.push_back(newShape);
        undoStack.push(newShape);
        // Clear redo stack when beginning a new action
        while(!redoStack.empty())
        {
            redoStack.pop();
        }
        break;
    }
    default:

        cout << "Invalid type. Please input again." << endl;
        break;
    }
}

void ShapeManagement::listShapes() const
{
    cout << ">>>>>All shapes: " << endl;
    for (auto iter = shapes.begin(); iter != shapes.end(); iter++)
    {
        (*iter)->outputData();
    }
}

Shape *ShapeManagement::at(int index)
{
    if (index >= shapes.size() || index < 0)
        return nullptr;
    auto iter = shapes.begin();
    advance(iter, index);
    return *iter;
}

Shape *ShapeManagement::removeAt(int index)
{
    // check index
    if (index >= shapes.size() || index < 0)
    {
        cerr << "Invalid index. Couldn't remove at " << index;
         return nullptr;
    }
    auto rmIter = shapes.begin();
    advance(rmIter, index);

    (*rmIter)->setUndoIndex(distance(shapes.begin(), rmIter));
    (*rmIter)->setCurrentAction(ActionEnum::Delete);
    undoStack.push(*rmIter);
    return *(shapes.erase(rmIter));
}

void ShapeManagement::undo()
{
    if (undoStack.size() == 0)
        return;
    Shape* undoShape{undoStack.top()};

    switch (undoShape->getCurrentAction())
    {
    case ActionEnum::Add:
    {
        auto iter = shapes.begin();
        advance(iter, undoShape->getUndoIndex());
        shapes.erase(iter);
        undoShape->setCurrentUDAction(ActionEnum::Delete);
        undoShape->removeCurrentAction();
        break;
    }
    case ActionEnum::Delete:
    {
        auto iter = shapes.begin();
        advance(iter, undoShape->getUndoIndex());
        shapes.insert(iter, undoShape);
        undoShape->setCurrentUDAction(ActionEnum::Add);
        undoShape->removeCurrentAction();
        break;
    }
    default:
        break;
    }
    redoStack.push(undoShape);
    undoStack.pop();
}

void ShapeManagement::redo()
{
    if (redoStack.size() == 0)
        return;
    Shape* redoShape{redoStack.top()};

    switch (redoShape->getCurrentUDAction())
    {
    case ActionEnum::Add:
    {
        auto iter = shapes.begin();
        advance(iter, redoShape->getUndoIndex());
        shapes.erase(iter);
        redoShape->setCurrentAction(ActionEnum::Delete);
        redoShape->removeCurrentUDAction();
        break;
    }
    case ActionEnum::Delete:
    {
        auto iter = shapes.begin();
        advance(iter, redoShape->getUndoIndex());
        shapes.insert(iter, redoShape);
        redoShape->setCurrentAction(ActionEnum::Add);
        redoShape->removeCurrentUDAction();
        break;
    }
    default:
        break;
    }
    undoStack.push(redoShape);
    redoStack.pop();
}
