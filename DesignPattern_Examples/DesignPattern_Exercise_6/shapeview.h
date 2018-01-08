#ifndef SHAPEVIEW_H
#define SHAPEVIEW_H
#include <cstdlib>
#include <list>
#include "shape.h"
using std::system;
using std::begin;
using std::end;
using std::list;
class ShapeView
{
private:
    string mainMenu;
    string addNewShapeMenu;
    int mainMenuSelection;
public:
    ShapeView();
    void viewMainMenu();
    int viewAddNewShapeMenu();
    int viewRemoveShapeMenu();
    int getMainMenuSelection() const;
    void viewAllShapes(const list<Shape *> &shapes) const;
};

#endif // SHAPEVIEW_H
