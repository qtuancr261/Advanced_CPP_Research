#include "shapemanagement.h"
int main(int argc, char *argv[])
{
    /*ShapeManagement manager;
    manager.addShape();
    manager.addShape();
    manager.removeAt(0);
    manager.addShape();
    manager.undo();
    manager.undo();
    manager.redo();
    manager.redo();
    manager.listShapes();
    //cout << "Test : " << manager.at(1)->area() << endl;
    //cout << manager.at(-1)<< endl;
    /*manager.removeAt(1);
    manager.removeAt(2);
    manager.listShapes();
    manager.undo();
    manager.listShapes();
    manager.removeAt(0);
    manager.listShapes();
    manager.undo();
    manager.undo();
    manager.listShapes();*/
    Shape* cicle = new Circle;
    cicle->justTest();
    Shape* rect = new Rectangle;
    rect->justTest();
   return 0; 
}
