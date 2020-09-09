#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>
#ifndef INVENTORY
#define INVENTORY  
using namespace std;

// class Inventory{
//     string brandName;
//     string itemName;
//     int quantity;
//     Inventory *next;
//     Inventory* top = NULL;

// public:
//     Inventory(){}
//     Inventory(string bname,string n, int q){
//         brandName = bname;
//         itemName = n;
//         quantity = q;
//     }
//     void setbrand(string b){brandName = b;}
//     void setname(string n) {itemName = n;}
//     void setquantity(int q){quantity = q;}
//     string getName (){return itemName;}

//     friend ostream& operator<<(ostream& out, const Inventory& I){
//         out << I.brandName << '\t' << I.itemName << '\t' << I.quantity << endl;
//         return out;
//     }
    // void push(string bname, string n, int q){
    //     Inventory* Node = new Inventory();
    //     Node->brandName = bname;
    //     Node->itemName = n;
    //     Node->quantity = q;
    //     Node->next = top;
    //     top = Node;
    // }

    // void pop(){
    //     if(top==NULL)
    //         cout << "Stack is empty.." << endl;
    //     else 
    //     {
    //         cout << "Element " << top->brandName << ", " << top->itemName << ", " << top->quantity << " removed" << endl;
    //         top = top->next;
    //     }
// };

struct Inventory{
    string brandName;
    string itemName;
    int quantity;
    struct Inventory* next;
};

struct Inventory* top;

void push(string brandName, string itemName, int quantity){
    struct Inventory* temp;
    temp = new Inventory();

    if(!temp)
    {
        cout << "Stack Overflow\n";
    }

    temp->brandName = brandName;
    temp->itemName = itemName;
    temp->quantity = quantity;
    temp->next = top;
    top = temp;
}

bool isEmpty(){
    return top == NULL;
}

void pop()
{
    struct Inventory* temp;

    if(isEmpty())
        cout << "\nStack Underflow" << endl;
    else
    {
        temp = top;
        top = top->next;
        temp->next = NULL;
        free(temp);
    }
}


void loadInventory() {
    string brandName;
    string itemName;
    int quantity;
    ifstream in("inventory.dat");
    while(getline(in,brandName, '\t'))
    {
        getline(in, itemName, '\t');
        in >> quantity;
        cout << brandName << " " << itemName << " " << quantity << " added" << endl;
        push(brandName, itemName, quantity);
        in.get();
    }
}


void showInventory() {
    int counter = 0;
    struct Inventory* temp;

    if(isEmpty())
        cout << "Nothing to show" << endl;
    else
    {
        temp = top;
        while(temp!=NULL)
        {
            counter++;
            cout << endl;
            cout << counter << ")" << temp->brandName << " " << temp->itemName << " " << temp->quantity << " displayed." << endl;
            temp = temp->next;
        }
    }
}

// void addItem(){
//     string brandName,itemName;
// 	int quantity;
// 	cout << "enter brand, item name, followed by quantity: \n";
// 	cout << "Brand Name: "; 
// 	getline(cin, brandName);
// 	cout << "Item Name: "; 
// 	getline(cin,itemName);
// 	cout << "Quantity: "; 
// 	cin >> quantity;
	
//     ofstream out("inventory.dat", ios::app);
//     out << brandName << '\t' << itemName << '\t' << quantity << '\n';
//     cout << "Item has been added successfully." << endl;
// }

// void removeItem()
// {
//     const char *fileName = "inventory.dat";
//     int line, defaultCounter = 1;
//     cout << "Select the item that you wish to remove (by line): ";
//     cin >> line;
//     ifstream inputFile(fileName);
//     ofstream temp("temp.dat", ofstream::out);
//     char c;

//     while (inputFile.get(c)) {
//         if (c == '\n') {
//             defaultCounter++;
//         }
//         if (defaultCounter != line) {
//             temp << c;
//         }
//     }
//     temp.close();
//     inputFile.close();

//     remove(fileName);
//     rename("temp.dat", fileName);
//     cout << "Item " << line << " has been removed." << endl;
// }

// string strLower(string a){
//     string b="";

//     for(int i=0; i<a.length(); i++)    
//         b+=tolower(a[i]);
//     return b;
// }




// void editItem()
// {
//     const char *filename = "inventory.dat";
//     int defaultCounter = 1, selected, quantity;
//     bool found;
//     string input, brandName, itemName;
//     ifstream inputFile(filename);
//     ofstream temp("temp.dat", ofstream::out);

//     cout << "Select the item that you wish to edit (by brand name / by item name / by quantity): ";
//     getline(cin, input);
//     cout << input << endl;
//     if(isdigit(input[0]))
//     {
//         while(getline(inputFile, brandName, '\t')){
//             defaultCounter++;
//             getline(inputFile, itemName, '\t');
//             inputFile >> quantity;
//             if(stoi(input) == quantity)
//             {
//                 selected = defaultCounter;
//                 found = true;
//                 break;
//             }
//         }
//     }
//     else
//     {   
//         while(getline(inputFile, brandName, '\t')){
//             defaultCounter++;
//             if(strLower(input) == strLower(brandName))
//             {
//                 getline(inputFile, itemName, '\t');
//                 inputFile >> quantity;
//                 found = true;
//                 break;
//             }
//             getline(inputFile, itemName, '\t');
//             if(strLower(input) == strLower(itemName))
//             {
//                 inputFile >> quantity;
//                 found = true; 
//                 break;
//             }
//         }
//     }


//     if(found==true) {
//         cout << endl << "Item of desired property " << "''" << input << " '' found. Details are as follows: " << endl;
//         cout << "Brand name: " << brandName << endl;
//         cout << "Item name: " << itemName << endl;
//         cout << "Quantity: " << quantity << endl;
//         cout << endl << endl << endl << "Please select which property to edit";
//     }
//     else cout << "Item not found." << endl;


//     //To-dos:
//     //Implement editing functions
// }
#endif
