#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#ifndef FoodMenu
#define FoodMenu
using namespace std;

struct menu{

string name;
float price;
};

class Consumable{
protected:
    float price;
    string name;
public:
    Consumable(float p, string n){
        price = p;
        name = n;
    }
    Consumable(){};
   // virtual void getInfo()=0;
   friend ostream& operator<<(ostream& out, const Consumable& c){
        out << c.name << '\t' << c.price << endl;
        return out;
    }
};

class Food:public Consumable{
public:
    Food(){};
    Food(string n, float p) {
        price = p;
        name = n;
    }
};

class Drink:public Consumable{
public:
    Drink(float p, string n){
        price = p;
        name = n;
    }
    Drink(){};
};

void showFoodMenu(){
    string name; float price;
    int counter =0;
    system("CLS");
    cout << "\tFOOD\n"
        << "----------------------\n\n";
    ifstream in("foodmenu.dat");

    while( getline(in,name, '\t'))
    {
        in >> price;
        in.ignore();
        counter++;
        if (name == "\n") break;
        cout << counter << ")  " << name << "  RM" << fixed << setprecision(2) << price << endl;
    }
}

void showDrinkMenu(){
    string name;float price;
    int counter2 =0;
    system("cls");

    cout << "\tDRINKS\n"
        << "----------------------\n\n";
    ifstream in("drinkmenu.dat");

    while (getline(in, name, '\t')){
        in >> price;
        in.ignore();
        counter2++;
        if ( name == "\n") break;
        cout << counter2 << ")  " << name << "  RM" << fixed << setprecision(2) << price << endl;

    }
}


void editFoodMenu(){
    int opt;
    char ans;

    cout << "Do you want to edit the food menu? (Y/n)";
    cin >> ans;
    while (ans == 'y' || ans == 'Y') {
        showFoodMenu();
        cout << endl << endl;
        cout << "Select your option:\n";
        cout << "1.) Add new food entry\n";
        cout << "2.) Remove an existing food entry\n";
        cout << endl;
        cout << "Option: ";
        cin >> opt;
        if (opt == 1) {
            string a;
            float b;
            cout << "Enter the name of the new food: ";
            cin.ignore();
            getline(cin, a);
            cout << "Enter the price of the new food: ";
            cin >> b;
            Food f1(a, b);
            ofstream add("foodmenu.dat", ios::app);
            add << f1;
            add.close();
        } else if (opt == 2) {
            const char *fileName = "foodmenu.dat";
            int line, defaultCounter = 1;
            cout << "Select the food that you wish to remove (by line): ";
            cin >> line;
            ifstream inputFile(fileName);
            ofstream temp("temp.dat", ofstream::out);
            char c;

            while (inputFile.get(c)) {
                if (c == '\n') {
                    defaultCounter++;
                }
                if (defaultCounter != line) {
                    temp << c;
                }
            }
            temp.close();
            inputFile.close();

            remove(fileName);
            rename("temp.dat", fileName);
            cout << "Line " << line << " has been removed." << endl;
        } else cout << "Invalid input." << endl;
        cout << "Do you want to continue? (Y/n)";
        cin >> ans;


    }
}

void editDrinkMenu() {
    int opt;
    char ans;

    cout << "Do you want to edit the drink menu? (Y/n)";
    cin >> ans;
    while (ans == 'y' || ans == 'Y') {
        showDrinkMenu();
        cout << endl << endl;
        cout << "Select your option:\n";
        cout << "1.) Add new drink entry\n";
        cout << "2.) Remove an existing drink entry\n";
        cout << endl;
        cout << "Option: ";
        cin >> opt;
        if (opt == 1) {
            string a;
            float b;
            cout << "Enter the name of the new drink: ";
            cin.ignore();
            getline(cin, a);
            cout << "Enter the price of the new drink: ";
            cin >> b;
            Drink d1(b, a);
            ofstream add("drinkmenu.dat", ios::app);
            add << d1;
            add.close();
        } else if (opt == 2) {
            const char *fileName = "drinkmenu.dat";
            int line, defaultCounter = 1;
            cout << "Select the food that you wish to remove (by line): ";
            cin >> line;
            ifstream inputFile(fileName);
            ofstream temp("temp.dat", ofstream::out);
            char c;

            while (inputFile.get(c)) {
                if (c == '\n') {
                    defaultCounter++;
                }
                if (defaultCounter != line) {
                    temp << c;
                }
            }
            temp.close();
            inputFile.close();

            remove(fileName);
            rename("temp.dat", fileName);
            cout << "Line " << line << " has been removed." << endl;
        }
        else cout << "Invalid input." << endl;
        cout << "Do you want to continue? (Y/n)";
        cin >> ans;
    }
}

void getFoodOrder(int foodchoice){
    string foodname; float foodprice;
    menu m;
    vector<menu> mtmp;
    ifstream readmenu("foodmenu.dat");
    ofstream foodlist("foodorderlist.dat", iostream::app);
    char word;
    int counter=1;

    while(readmenu.get(word))
    {
        if ( word == '\n'){
            counter++;
        }else{
            if( counter == foodchoice)
            {
                if (getline(readmenu,foodname, '\t'))
                {
                    readmenu >> foodprice;
                    m.name = word + foodname;
                    m.price = foodprice;
                    mtmp.push_back(m);
                    foodlist << mtmp.front().name <<'\t'<< mtmp.front().price << endl;
                }
            }
        }
    }
    readmenu.close();
    foodlist.close();
}
void getDrinkOrder(int drinkchoice){
    string drinkname; float drinkprice;
    menu m1;
    vector<menu> mtmp1;
    ifstream readmenu1("drinkmenu.dat");
    ofstream foodlist("foodorderlist.dat", iostream::app);
    char word;
    int counter=1;

    while(readmenu1.get(word))
    {
        if ( word == '\n'){
            counter++;
        }else{
            if( counter == drinkchoice)
            {
                if (getline(readmenu1,drinkname, '\t'))
                {
                    readmenu1 >> drinkprice;
                    m1.name = word + drinkname;
                    m1.price = drinkprice;
                    mtmp1.push_back(m1);
                    foodlist << mtmp1.front().name <<'\t'<< mtmp1.front().price << endl;
                }
            }
        }
    }
}
#endif
