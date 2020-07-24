
#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "windows.h"
#include "FoodMenu.h"
using namespace std;
HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE);
const char *fileName = "foodorderlist.dat";

void viewSummary(){
    system("CLS");
    ifstream master("summary.dat");
    string content;
    while(getline(master, content))
    {
        cout << content << endl;
    }
    cout << "----------------------------\n";
    getch();



}
void getDelivery(){
    srand(time(0));
    system("CLS");
    int eta;eta = rand()%25;(eta==0?eta=1:eta = rand()%25);
    string deliveryName;
    string platenumber;
    string phonenumber;
    char c;
    int defaultCounter =1;
    int lineNumber;
    lineNumber = rand()%6;
    if (lineNumber ==0) lineNumber++;

    ifstream delivery("delivery.dat");
    ofstream temp("temp.dat");

    while(delivery.get(c))
        {
            if (c == '\n')
            {
                defaultCounter++;
            }else{
                if (defaultCounter == lineNumber)
                {
                    temp << c;
                }
            }
        }
    temp.close();

    ifstream temp1("temp.dat");
    while (getline(temp1,deliveryName, '\t'))
    {
        getline(temp1, platenumber, '\t');
        getline(temp1, phonenumber);
        if (deliveryName == "\n") break;
        cout<< endl;
        cout<< "Delivery Guy: " << deliveryName <<endl
            << "Vehicle Registration Number: " << platenumber << endl
            << "Delivery Guy Phone Number: " << phonenumber << endl;
    }
    delivery.close();
    temp1.close();
    cout <<endl << endl;
    cout<< "Estimated time of arrival: " << eta << " minutes."<< endl
        << "If somehow you need to leave a message to our dispatcher, feel free to use the phone number provided :)" << endl;


}
void getReceipt(){
    system("CLS");
    ifstream receipt(fileName);
    string objName; float price, total=0;
    cout << "\t\t\t    RECEIPT\n"
        <<"---------------------------------------------------------------\n\n";
    while (getline(receipt, objName, '\t')){
        if (objName == "\n") break;
        receipt >> price;
        cout<< objName << " \t\tRM" << fixed << setprecision(2) << price << endl;
        total+=price;
    }
    cout << endl << endl;
    cout << "\t\t\tYour total is : RM" << fixed << setprecision(2) << total;
    cout << endl << endl;
    getch();
}

void mainMenu(){
    m:
    int au;

    cin.clear();
    cin.sync();
    system("CLS");
    string name;

    cout<<"\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n";
        SetConsoleTextAttribute(color, 15);
        cout<<"\t          ^v^ HAPPY RESTAURANT ^v^\n\n";
        SetConsoleTextAttribute(color, 7);
        cout<<"\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n\n";
        SetConsoleTextAttribute(color, 55);
        cout<<"                                                                                                                        "<<endl<<endl;
        SetConsoleTextAttribute(color, 15);
    cout << "\t      --------------------------------\n";
    cout << "\t      | WELCOME TO HAPPY RESTAURANT! |\n";
    cout << "\t      --------------------------------\n\n";
    cout << "\tI am: \n";
    cout << "\t1. an administrator\n";
    cout << "\t2. a user\n\n";
    cout << "\tYour choice: ";
    cin >> au;
    system("CLS");

    switch (au) {
    case 1:{
        string pswd;
        system("CLS");
        cout << "Please enter the password: ";
        cin >> pswd;
        system("CLS");

        if (pswd=="admin")
        {
            int option;
            cout << "Admin Control Panel\n\n"
            <<"1. View Sales Summary\n"
            <<"2. Edit Foods Menu\n"
            <<"3. Edit Drinks Menu\n"
            <<"4. Logout\n";
            cout << "Enter option:";
            cin >> option;
            switch(option)
            {
            case 1:
                viewSummary();
                break;
            case 2:
                editFoodMenu();
                break;
            case 3:
                editDrinkMenu();
                break;
            case 4:
                cout << "Logging out";
                getch();
                break;
            }
            goto m;
        }
        else
        {
            cout << "\nWrong password!";
            goto m;
        }
        break;}

    case 2:{
        cout << "Please input a name: ";
        cin >> name;

        if(name == "0"){exit(1);}else if (name == ""){ cout << endl << endl <<"\t\tPlease input a name!";getch(); goto m;}
        else
        {
            int choice;
            char yesorno;
            showFoodMenu();
            cout << endl << endl;
            do{
                cout << "Enter choice for foods: ";
                cin >> choice;
                getFoodOrder(choice);
                cout << "Do you wish to add more foods?(Y/n):";
                cin >>  yesorno;
                yesorno = tolower(yesorno);
            }while(yesorno == 'y');
            yesorno = 0;
            cout << endl << endl;
            char yesorno2;
            showDrinkMenu();
            cout << endl << endl;
            do{
                cout << "Enter choice for drinks: ";
                cin >> choice;
                getDrinkOrder(choice);
                cout << "Do you wish to add more drinks?(Y/n):";
                cin >>  yesorno2;
                yesorno2 = tolower(yesorno2);
            }while(yesorno2 == 'y');
        }
        ofstream master("summary.dat", iostream::app);
        ifstream foodlist("foodorderlist.dat");
        string line;
        master << name << endl;
        master << "--------------" << endl;
        while (foodlist.good())
        {
            getline(foodlist, line);
            master << line << endl;
        }
        master.close();
        foodlist.close();
        break;}

    default:{
        cout << "\nInvalid input! Please try again!";
        goto m;}
    }
}

int main (){

mainMenu();
system("CLS");
getReceipt();
getDelivery();
getch();
remove("foodorderlist.dat");
remove("temp.dat");
}


