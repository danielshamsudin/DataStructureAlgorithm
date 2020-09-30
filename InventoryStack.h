#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>
#ifndef INVENTORY
#define INVENTORY  
using namespace std;


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
        cout << "No.\t" << "Brand\t" << "Item\t" << "Quantity\t" << "Date\n";
        cout << "_________________________________________________\n";
        while(temp!=NULL)
        {
            counter++;
            cout << endl;
            cout << counter << ")\t" << temp->brandName << "\t" << temp->itemName << "\t" << temp->quantity << endl;
            temp = temp->next;
        }
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
    out << brandName << '\t' << itemName << '\t' << quantity << '\n';
    cout << "Item has been added successfully." << endl;
}


Inventory* SortedMerge(Inventory* a, Inventory* b, int scenario)
{
    Inventory* result = NULL;

    if(a==NULL)               //Base case 1
        return(b);
    else if (b == NULL)       //Base case 2 
        return(a);

    if(scenario==1) {          //Sorting scenario 1 (Ascending Brand Name Sorting)
        if (a->brandName <= b->brandName) {
            result = a;       
            result->next = SortedMerge(a->next, b, scenario);
        }
        else {
            result = b;
            result->next = SortedMerge(a, b->next, scenario);
        }
    }
    else if(scenario==2) {          //Sorting scenario 2 (Descending Brand Name Sorting)
        if (a->brandName > b->brandName) {
            result = a;       
            result->next = SortedMerge(a->next, b, scenario);
        }
        else {
            result = b;
            result->next = SortedMerge(a, b->next, scenario);
        }
    }
    else if(scenario==3) {      //Sorting scenario 3 (Ascending Item Name Sorting)
        if (a->itemName <= b->itemName) {
            result = a;
            result->next = SortedMerge(a->next, b, scenario);
        }
        else {
            result = b;
            result->next = SortedMerge(a, b->next, scenario);
        }
    }
    else if(scenario==4) {      //Sorting scenario 4 (Descending Item Name Sorting)
        if (a->itemName > b->itemName) {
            result = a;
            result->next = SortedMerge(a->next, b, scenario);
        }
        else {
            result = b;
            result->next = SortedMerge(a, b->next, scenario);
        }
    }
    else if(scenario==5) {      //Sorting scenario 5 (Ascending Item Quantity Sorting)
        if (a->quantity <= b->quantity) {
            result = a;
            result->next = SortedMerge(a->next, b, scenario);
        }
        else {
            result = b;
            result->next = SortedMerge(a, b->next, scenario);
        }
    }
    else if(scenario==6) {      //Sorting scenario 6 (Descending Item Quantity Sorting)
        if (a->quantity > b->quantity) {
            result = a;
            result->next = SortedMerge(a->next, b, scenario);
        }
        else {
            result = b;
            result->next = SortedMerge(a, b->next, scenario);
        }
    }
    return(result);
}

void FrontBackSplit(Inventory* source, Inventory** frontRef, Inventory** backRef)
{
    Inventory* fast;
    Inventory* slow;
    slow = source;
    fast = source->next;

    while(fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

void MergeSort(Inventory** headRef, int scenario) {
    Inventory* head = *headRef;
    Inventory* temp1;
    Inventory* temp2;

    if((head == NULL) || (head->next == NULL))  // base case for recursion - 0 or 1 
        return;
    
    FrontBackSplit(head, &temp1, &temp2);

    MergeSort(&temp1, scenario);  //Recursive sublist sorting
    MergeSort(&temp2, scenario);  //Recursive sublist sorting

    *headRef = SortedMerge(temp1, temp2, scenario);   //merge two sorted linked lists 
}

void sortAndDisplay() {
    std::system("clear");  //use ("cls") on Windows
    int entry;
    showInventory();
    cout << "Enter option to sort by: " << endl << endl;
    cout << "1.) By brand name (Ascending)" << endl;
    cout << "2.) By brand name (Descending)" << endl;
    cout << "3.) By item name (Ascending)" << endl;
    cout << "4.) By item name (Descending)" << endl;
    cout << "5.) By item quantity (Ascending)" << endl;
    cout << "6.) By item quantity (Descending)" << endl << endl << endl;

    cout << "Option: ";
    cin >> entry;
    if(entry>0 && entry<7)
        MergeSort(&top, entry);
    else
        cout << "Please enter one of the numbers listed!" << endl;
}
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
