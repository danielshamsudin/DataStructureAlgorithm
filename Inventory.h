#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <stdlib.h>
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
    string tmpBrand, tmpItem;
    char* userInput;
    char c;
    ifstream inputFile (filename);
    ofstream tempFile ("temp.dat");
    cout << "Please enter the Brand Name, Item Name or Quantity that you want to modify: ";
    cin >> userInput; 
    if (isdigit(userInput[0]))
    {
        while (inputFile.get(c) && c != '\t')
        {
            
        }
    } // search for Qty
    else
    {
        
    } // search for BrandName, ItemName

}
#endif
