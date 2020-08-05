#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>
#ifndef INVENTORY
#define INVENTORY  
using namespace std;

class Inventory{
    string brandName;
    string itemName;
    int quantity;
public:
    Inventory(){}
    Inventory(string bname,string n, int q){
        brandName = bname;
        itemName = n;
        quantity = q;
    }
    void setbrand(string b){brandName = b;}
    void setname(string n) {itemName = n;}
    void setquantity(int q){quantity = q;}
    string getName (){return itemName;}

    friend ostream& operator<<(ostream& out, const Inventory& I){
        out << I.brandName << '\t' << I.itemName << '\t' << I.quantity << endl;
        return out;
    }
};


void showInventory(){
    string brandName;
    string itemName;
    int quantity;
    int counter = 0;
    ifstream in("inventory.dat");
    while(getline(in,brandName, '\t'))
    {
        counter++;
        getline(in, itemName, '\t');
        in >> quantity;
        cout<<counter << ")" << brandName<<'\t'<< itemName << '\t'<< quantity << '\n';
        in.get();
    }
}

void addItem(){
    string brandName,itemName;
	int quantity;
	cout << "enter brand, item name, followed by quantity: \n";
	cout << "Brand Name: "; 
	getline(cin, brandName);
	cout << "Item Name: "; 
	getline(cin,itemName);
	cout << "Quantity: "; 
	cin >> quantity;
	
    ofstream out("inventory.dat", ios::app);
    Inventory tmp(brandName, itemName, quantity);
    out << tmp;
    cout << "Item " << tmp.getName() << " has been added successfully.";
}

void removeItem()
{
    const char *fileName = "inventory.dat";
    int line, defaultCounter = 1;
    cout << "Select the item that you wish to remove (by line): ";
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
    cout << "Item " << line << " has been removed." << endl;
}

void editItem()
{
    const char *filename = "inventory.dat";
    int defaultCounter = 1, selector, selected, quantity;
    bool found;
    string input, brandName, itemName;

    cout << "Select the item that you wish to edit (by brand name / by item name / by quantity): ";
    getline(cin, input);
    ifstream inputFile(filename);
    ofstream temp("temp.dat", ofstream::out);
    char c;

    cout << input << endl;
    if(isdigit(input[0]))
    {
        selector = stoi(input);
        while(getline(inputFile, brandName, '\t')){
            defaultCounter++;
            getline(inputFile, itemName, '\t');
            inputFile >> quantity;
            if(selector == quantity){
                selected = defaultCounter;
                found = true;
                break;
            }
        }
    }
    else
    { 
        for(char i: input) 
            putchar(tolower(input[i]));  
        while(getline(inputFile, brandName, '\t')){
            for(char i: brandName)
                putchar(tolower(brandName[i]));
            defaultCounter++;
            if(input == brandName)
            {
                getline(inputFile, itemName, '\t');
                inputFile >> quantity;
                found = true;
                break;
            }
            getline(inputFile, itemName, '\t');
            for(char i: itemName)
                putchar(tolower(itemName[i]));
            if(input == itemName)
            {
                inputFile >> quantity;
                found = true; 
                break;
            }
        }
    }
    

    if(found==true) {
        cout << endl << "Item of desired property " << "''" << input << " '' found. Details are as follows: " << endl;
        cout << "Brand name: " << brandName << endl;
        cout << "Item name: " << itemName << endl;
        cout << "Quantity: " << quantity << endl;
        cout << endl << endl << endl << "Please select which property to edit";
    }
    else cout << "You lost" << endl;


    //To-dos:
    //Implement tolower search properly
    //Implement editing functions
}
#endif
