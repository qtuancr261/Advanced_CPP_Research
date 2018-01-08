#include "shapemanagement.h"
ShapeManagement::ShapeManagement() : factory{new Shape2DFactory}
{

}

ShapeManagement::~ShapeManagement()
{
    cout << "Releasing Memory" << endl;
    delete factory;
    Shape* tempShapePtr{nullptr};
    while(!undoStack.empty())
    {
        tempShapePtr = undoStack.top();
        if (!shapeMatch(tempShapePtr))
        {
            delete tempShapePtr;
        }
        undoStack.pop();
    }
    while(!redoStack.empty())
    {
        tempShapePtr = redoStack.top();
        if (!shapeMatch(tempShapePtr))
        {
            delete tempShapePtr;
        }
        redoStack.pop();
    }
    while(!shapes.empty())
    {
        tempShapePtr = shapes.back();
        delete tempShapePtr;
        shapes.pop_back();
    }
}

void ShapeManagement::addShape()
{
    int shapeType{0};
    Shape* newShape{};
    shapeType = menu.viewAddNewShapeMenu();
    switch (shapeType)
    {
    case 1:
        {
            newShape = factory->createStraightShape();
            break;
        }
    case 2:
        {
            newShape = factory->createCurvedShape();
            break;
        }
    }
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
}

void ShapeManagement::listShapes() const
{
    cout << ">>>>>All shapes: " << endl;
    for (auto iter = shapes.begin(); iter != shapes.end(); iter++)
    {
        (*iter)->outputData();
    }
}

bool ShapeManagement::shapeMatch(Shape *shape) const
{
    for (auto iter = shapes.begin(); iter != shapes.end(); iter++)
    {
        if (*iter == shape)
            return true;
    }
    return false;
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
        cerr << "Invalid index. Couldn't remove at " << index << endl;
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
    {
        cout << "Couldn't undo" << endl;
        return;
    }
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
    cout << "Undo successfully" << endl;
}

void ShapeManagement::redo()
{
    if (redoStack.size() == 0)
    {
        cout << "Couldn't redo" << endl;
        return;
    }
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
    cout << "Redo successfully" << endl;
}

void ShapeManagement::exec()
{
    do
    {
         menu.viewMainMenu();
         switch (menu.getMainMenuSelection())
         {
         case 1:
             addShape();
             cout << "Added successfully. ";
             system("pause");
             break;
         case 2:
             removeAt(menu.viewRemoveShapeMenu());
             system("pause");
             break;
         case 3:
             undo();
             system("pause");
             break;
         case 4:
             redo();
             system("pause");
             break;
         case 5:
             menu.viewAllShapes(shapes);
             system("pause");
             break;
         case 6:
             break;
         default:
             break;
         }
    }while(menu.getMainMenuSelection() != 6);

}
