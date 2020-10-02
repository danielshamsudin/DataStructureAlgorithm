#include <iostream>
#include <stdlib.h>
#include "InventoryStack.h"


using namespace std;

void menu()
{
    int choice;
    char chs;
    cout << "-------------------------\n";
    cout << "|\tMain Menu\t|\n";
    cout << "-------------------------\n";
    cout << "|    1. Show Inventory  |\n";
    cout << "|    2. Add Item        |\n";
    cout << "|    3. Remove Item     |\n";
    cout << "|    4. Edit Item       |\n";
    cout << "|    5. Exit            |\n";
    cout << "-------------------------\n";
    cout << "Please enter menu choice:";
    choice = InventoryStack::int_range_validation(1,5,"Please enter the correct menu choice! :");

    switch (choice)
    {
        case 1:
            system("CLS");
            InventoryStack::showInventoryWithExpiryDate();
            cout << "Do you wish to sort these items? (y/n):";
            cin >> chs;
            if (chs =='y' || chs == 'Y')
            {
                InventoryStack::sortAndDisplay();
                InventoryStack::showInventoryWithExpiryDate();
            }
            break;
        case 2:
            system("CLS");
            InventoryStack::addItem();
            cin.get();
            InventoryStack::showInventoryWithExpiryDate();
            break;
        case 3:
            system("CLS");
            InventoryStack::showInventoryWithExpiryDate();
            InventoryStack::removeItem();
            InventoryStack::loadInventory();
            break;
        case 4:
            system("CLS");
            InventoryStack::editItem();
            break;
        case 5:
            system("CLS");
            cout << "Thank you!\n";
            cin.get();
            exit(0);
            break;
        default:
            break;
    }
}

int main()
{
    char cont;
    InventoryStack::loadInventory();
    do
    {
        system("CLS");
        menu();
        cout << "Do you wish to continue? (y/n):";
        cin >> cont;
    }while(cont == 'y' || cont == 'Y');
}



















