#include "shapeview.h"

ShapeView::ShapeView()
    : mainMenu{"---------MENU 1.0---------\n"
               "1. Add new shape.\n"
               "2. Remove shape.\n"
               "3. Undo.\n"
               "4. Redo.\n"
               "5. View All shape.\n"
               "6. Exit.\n"
               "----> You choice: "},
      addNewShapeMenu{"1. Rectangle.\n"
                      "2. Circle.\n"
                      "---> shape type: "},
      mainMenuSelection{0}
{

}

void ShapeView::viewMainMenu()
{
    do
    {
        system("cls");
        cout << mainMenu;
        cin >> mainMenuSelection;
    }while(mainMenuSelection <= 0 || mainMenuSelection > 6);
    //return mainMenuSelection;
}

int ShapeView::viewAddNewShapeMenu()
{
    int selection{};
    do
    {
        system("cls");
        cout << addNewShapeMenu;
        cin >> selection;
    }while(selection <= 0 || selection > 2);
    return selection;
}

int ShapeView::viewRemoveShapeMenu()
{
    int selection{};
    system("cls");
    cout << "Please input the shape's index you want to remove: ";
    cin >> selection;
    return selection;
}

int ShapeView::getMainMenuSelection() const
{
    return mainMenuSelection;
}

void ShapeView::viewAllShapes(const list<Shape *> &shapes) const
{
    system("cls");
    cout << ">>>>>All shapes: " << endl;
    for (auto iter = begin(shapes); iter != end(shapes); iter++)
    {
        (*iter)->outputData();
    }
}
