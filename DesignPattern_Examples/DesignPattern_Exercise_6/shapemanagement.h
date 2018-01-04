#ifndef SHAPEMANAGEMENT_H
#define SHAPEMANAGEMENT_H
#include <cstdlib>
#include "rectangle.h"
#include "circle.h"
#include "list"
#include "stack"
using std::stack;
using std::list;
using std::advance;
using std::distance;
class ShapeManagement
{
private:
    list<Shape*> shapes;
    stack<Shape*> undoStack;
    stack<Shape*> redoStack;
public:
    ShapeManagement();
    virtual ~ShapeManagement();
    void addShape();
    void listShapes() const;
    Shape *at(int index);
    Shape* removeAt(int index);
    void undo();
    void redo();
};

#endif // SHAPEMANAGEMENT_H
