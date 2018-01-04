#include "menu.h"

Menu::Menu()
    : mainMenuContent{"----------------------------------\n"
                      "DOUBLY LINKED LIST OPERATIONS MENU\n"
                      "----------------------------------\n"
                      "1. Add a new item\n"
                      "2. Delete an item\n"
                      "3. Show number of items\n"
                      "4. Find max item\n"
                      "5. Find min item\n"
                      "6. Find item\n"
                      "7. Print all items\n"
                      "8. Exit\n"
                      "-> Enter your choice: "},
      dataList{},
      mainMenuSelection{0}
{
 // default constructor
}

void Menu::initMenu()
{
    do
    {
        system("cls");
        cout << mainMenuContent;
        cin >> mainMenuSelection;
        switch (mainMenuSelection)
        {
        case 1:
        {
            system("cls");
            int newValue{};
            cout << "Input your item data: ";
            cin >> newValue;
            int index{};
            cout << "Input the index of your new item data: ";
            cin >> index;
            dataList.insertAt(index, newValue);
            break;
        }
        case 2:
        {
            system("cls");
            int index{};
            cout << "Input the index of the item data you want to delete: ";
            cin >> index;
            dataList.removeAt(index);
            system("pause");
            break;
        }
        case 3:
            system("cls");
            cout << "The number of items: " << dataList.size() << endl;
            system("pause");
            break;
        case 4:
            system("cls");
            cout << "The min item: " << dataList.findMinItem() << endl;
            system("pause");
            break;
        case 5:
            system("cls");
            cout << "The max item: " << dataList.findMaxItem() << endl;
            system("pause");
            break;
        case 6:
        {
            system("cls");
            int value{};
            cout << "Input your item data: ";
            cin >> value;
            dataList.findIndexOfItem(value);
            system("pause");
            break;
        }
        case 7:
            system("cls");
            dataList.printList();
            system("pause");
            break;
        default:
            break;
        }
    }while (mainMenuSelection != 8);
}
