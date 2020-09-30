#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "Date.h"
#ifndef INVENTORY
#define INVENTORY
using namespace std;

class Inventory{
    string brandName;
    string itemName;
    int quantity;
    Date date;
public:
    Inventory(){}
    Inventory(string brandname, string itemname, int quantity)
    {
        this->brandName = brandname;
        this->itemName = itemname;
        this->quantity = quantity;
    }
    Inventory(string brandname,string itemname, int quantity, Date expiryDate){
        this->brandName = brandname;
        this->itemName = itemname;
        this->quantity = quantity;
        this->date = expiryDate;
    }
    void setbrand(string b){brandName = b;}
    void setname(string n) {itemName = n;}
    void setquantity(int q){quantity = q;}
    string getName (){return itemName;}

    friend ostream& operator<<(ostream& out, const Inventory& I){
        out << I.brandName << '\t' << I.itemName << '\t' << I.quantity << '\t' <<I.date << endl;
        return out;
    }
};


void showInventory(){
    string brandName;
    string itemName;
    int quantity;
    string expire;
    int counter = 0;
    ifstream in("inventory.dat");
    while(getline(in,brandName, '\t'))
    {
        counter++;
        getline(in, itemName, '\t');
        in >> quantity;
        in >> expire;
        cout<<counter << ")" << brandName<<'\t'<< itemName << '\t'<< quantity << '\t' << expire <<'\n';
        in.get();
    }
}

 void addItem(){
    string brandName,itemName;
    int quantity, day, month, year;
    cout << "enter brand, item name,quantity and followed by expiry date in the format of dd MM yy : \n";
    cout << "Brand Name: ";
    cin.ignore();
    getline(cin, brandName);
    cout << "Item Name: ";
    getline(cin,itemName);
    cout << "Quantity: ";
    cin >> quantity;
    cout << "Date: \n";
    cin >> day >> month >> year;
    Date dte(day,month,year);
    ofstream out("inventory.dat", ios::app);
    Inventory tmp(brandName, itemName, quantity, dte);
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

// void editItem()
// {
//     const char *filename = "inventory.dat";
//     string tmpBrand, tmpItem;
//     char* userInput;
//     char c;
//     ifstream inputFile (filename);
//     ofstream tempFile ("temp.dat");
//     cout << "Please enter the Brand Name, Item Name or Quantity that you want to modify: ";
//     cin >> userInput;
//     if (isdigit(userInput))
//     {
//         while (inputFile.get(c) && c != '\t')
//         {
//
//         }
//     } // search for Qty
//     else
//     {
//
//     } // search for BrandName, ItemName
//
// }
#endif
