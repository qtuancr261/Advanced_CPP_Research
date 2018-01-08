#ifndef SHAPEMANAGEMENT_H
#define SHAPEMANAGEMENT_H
#include <cstdlib>
#include "rectangle.h"
#include "circle.h"
#include "list"
#include "stack"
#include "Factory/shape2dfactory.h"
#include "shapeview.h"
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
    ShapeView menu;
    Shape2DFactory* factory;
public:
    ShapeManagement();
    virtual ~ShapeManagement();
    void addShape();
    void listShapes() const;
    bool shapeMatch(Shape* shape) const;
    Shape *at(int index);
    Shape* removeAt(int index);
    void undo();
    void redo();
    void exec();
};

#endif // SHAPEMANAGEMENT_H
