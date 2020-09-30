#include <iostream>
#include <stdlib.h>
#include "Inventory.h"

using namespace std;

void menu()
{
    int choice;

    cout << "1. Show Inventory\n";
    cout << "2. Add Item\n";
    cout << "3. Remove Item\n";
    cout << "4. Edit Item\n";
    cout << "5. Exit\n";
    cout << "Please enter menu choice:";
    cin >> choice;

    switch (choice)
    {
        case 1:
            system("CLS");
            showInventory();
            break;
        case 2:
            system("CLS");
            addItem();
            break;
        case 3:
            system("CLS");
            showInventory();
            cout << endl;
            removeItem();
            break;
        default:
            break;
    }
}

int main()
{
    system("CLS");
    menu();
}

