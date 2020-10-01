#include <iostream>
#include <fstream>
#include <string>
#include "Date.h"
#ifndef INVENTORY_STACK
#define INVENTORY_STACK




using namespace std;

struct Inventory
{
    string brandName;
    string itemName;
    int quantity;
    Date date;
    Inventory* next;
};

Inventory* top;


void push(string brandName, string itemName, int quantity, Date expiryDate)
{
    Inventory* temp;
    temp = new Inventory();

    if(!temp)
    {
        cout << "Stack Overflow\n";
    }

    temp->brandName = brandName;
    temp->itemName = itemName;
    temp->quantity = quantity;
    temp->date = expiryDate;
    temp->next = top;
    top = temp;
}

bool isEmpty()
{
    return top == NULL;
}

void pop()
{
    Inventory* temp;

    if(isEmpty())
        cout << "\nStack Underflow" << endl;
    else {
        temp = top;
        top = top->next;
        temp->next = NULL;
        free(temp);
    }
}


void loadInventory()
{
    string brandName;
    string itemName;
    string expire;
    Date temp;
    int quantity, d, m, y;
    ifstream in("inventory.dat");
    while(getline(in,brandName, '\t'))
    {
        getline(in, itemName, '\t');
        in >> quantity;
        in >> temp;
        push(brandName, itemName, quantity, temp);
        in.get();
    }
}


void showInventory()
{
    int counter = 0;
    Inventory* temp;

    if(isEmpty())
        cout << "Nothing to show" << endl;
    else {
        temp = top;
        cout << "No.\t" << "Brand\t" << "Item\t" << "Quantity\t" << "Expiry Date\n";
        cout << "_________________________________________________\n";
        while(temp!=NULL)
        {
            counter++;
            cout << endl;
            cout << counter << ")\t" << temp->brandName << "\t" << temp->itemName << "\t" << temp->quantity << "\t" << temp->date.getDate() << endl;
            temp = temp->next;
        }
    }
}

void addItem()
{
    string brandName,itemName;
	int quantity, day, month, year;
	cout << "enter brand, item name, quantity, and expiry date: \n";
	cout << "Brand Name: "; 
	getline(cin, brandName);
	cout << "Item Name: "; 
	getline(cin,itemName);
	cout << "Quantity: "; 
	cin >> quantity;
    cout << "Date: \n";
    cin >> day >> month >> year;
    Date dte(day, month, year);  
    ofstream out("inventory.dat", ios::app);
    out << brandName << '\t' << itemName << '\t' << quantity << '\t' << dte << '\n';
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
    else if(scenario==7) {      //Sorting scenario 7 (Ascending Date Sorting)
        if (a->date.getYear() <= b->date.getYear()) {
            result = a;
            result->next = SortedMerge(a->next, b, scenario);
        }
        else {
            result = b;
            result->next = SortedMerge(a, b->next, scenario);
        }
    }
    else if(scenario==8) {      //Sorting scenario 8 (Descending Date Sorting)
        if (a->date.getYear() > b->date.getYear()) {
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

void MergeSort(Inventory** headRef, int scenario)
{
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

void sortAndDisplay()
{
    std::system("clear");  //use ("cls") on Windows
    int entry;
    showInventory();
    cout << "Enter option to sort by: " << endl << endl;
    cout << "1.) By brand name (Ascending)" << endl;
    cout << "2.) By brand name (Descending)" << endl;
    cout << "3.) By item name (Ascending)" << endl;
    cout << "4.) By item name (Descending)" << endl;
    cout << "5.) By item quantity (Ascending)" << endl;
    cout << "6.) By item quantity (Descending)" << endl;
    cout << "7.) By date (Ascending)" << endl;
    cout << "8.) By date (Descending)" << endl;

    cout << "Option: ";
    cin >> entry;
    if(entry>0 && entry<9)
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

string strLower(string a){
    string b="";

    for(int i=0; i<a.length(); i++)    
        b+=tolower(a[i]);
    return b;
}


Inventory* middle(Inventory* start, Inventory* last) //utility fn for binSearch, searches for middle node
{
    if(start==NULL)
        return NULL;
    
    Inventory* slow = start;
    Inventory* fast = start -> next;

    while(fast!=last)
    {
        fast = fast -> next;
        if(fast!=last)
        {
            slow = slow -> next;
            fast = fast -> next;
        }
    }

    return slow;

}

Inventory* binSearch(Inventory* head, int qty) //overloaded binSearch fn for quantity
{
    Inventory* start = head;
    Inventory* last = NULL;

    do
    {
        Inventory* mid = middle(start, last);

        if(mid==NULL)
            return NULL;

        if(mid->quantity==qty) {
            cout << mid->quantity;
            return mid;
        }

        else if(mid->quantity < qty)
            start = mid->next;
        
        else
            last = mid;
        
    } while (last == NULL || last!=start);

    return NULL;
}

Inventory* binSearch(Inventory* head, string input, int choice) //overloaded binSearch fn for string-based data
{
    Inventory* start = head;
    Inventory* last = NULL;

    do
    {
        Inventory* mid = middle(start, last);

        if(mid==NULL)
            return NULL;

        if(choice==1) {
            if(mid->brandName==input)
                return mid;
            else if(mid->brandName < input)
                start = mid->next;
            else
                last = mid;
        }
        else if(choice==2) {
            if(mid->itemName==input)
                return mid;
            else if(mid->brandName < input)
                start = mid->next;
            else
                last = mid;
        }         
    } while (last == NULL || last!=start);

    return NULL;
}

Inventory* binSearch(Inventory* head, Date d) //overloaded binSearch fn for date-based data
{
    Inventory* start = head;
    Inventory* last = NULL;

    do
    {
        Inventory* mid = middle(start, last);

        if(mid==NULL)
            return NULL;

        if(mid->date.getYear()==d.getYear()) {
            if(mid->date.getMonth()==d.getMonth()){
                if(mid->date.getDay()==d.getDay())
                    return mid;
                else if(mid->date.getDay() < d.getDay())
                    start = mid->next;
            }
            else if(mid->date.getMonth() < d.getMonth())
                start = mid->next;
        }
        else if(mid->date.getYear() < d.getYear())
            start = mid->next;
        
        else
            last = mid;
        
    } while (last == NULL || last!=start);

    return NULL;
}



void editItem()
{
    const char *filename = "inventory.dat";
    int defaultCounter = 1, selected, quantity, choice;
    bool found;
    string input, brandName, itemName;
    Date date;
    ifstream inputFile(filename);
    ofstream temp("temp.dat", ofstream::out);

    cout << "Search the item that you wish to edit: \n" << endl;
    cout << "1.) Search by Brand name: " << endl;
    cout << "2.) Search by Item name: " << endl;
    cout << "3.) Search by Item quantity: " << endl;
    cout << "4.) Search by expiry date: \n" << endl << endl;
    cout << "Choice: ";

    cin >> choice;

    if(choice==1) {
        cout << "\n\nEnter Brand Name: ";
        cin >> input;
        MergeSort(&top, 1);
        if(binSearch(top, input, choice) == NULL)
            cout << "Item with brand name " << input << " not found." << endl;
        else {
            Inventory* info = binSearch(top, input, choice);

            cout << "Item has been found, bitch. Details are as follows:\n" << endl;
            cout << "Brand name: " << info->brandName << endl;
            cout << "Item name: " << info->itemName << endl;
            cout << "Item quantity: " << info->quantity << endl;
            cout << "Expiry date: " << info->date.getDate() << endl;
        }
    }
    if(choice==2) {
        cout << "\n\nEnter Item Name: ";
        cin >> input;
        MergeSort(&top, 3);
        if(binSearch(top, input, choice) == NULL)
            cout << "Item with name " << input << " not found." << endl;
        else {
            Inventory* info = binSearch(top, input, choice);

            cout << "Item has been found, bitch. Details are as follows:\n" << endl;
            cout << "Brand name: " << info->brandName << endl;
            cout << "Item name: " << info->itemName << endl;
            cout << "Item quantity: " << info->quantity << endl;
            cout << "Expiry date: " << info->date.getDate() << endl;
        }
    }
    else if(choice==3) {
        cout << "\n\nEnter Item Quantity: ";
        cin >> input;
        MergeSort(&top, 5);
        if(binSearch(top, stoi(input)) == NULL)
            cout << "Item is not found faggot" << endl;
        else {
            Inventory* info = binSearch(top, stoi(input));

            cout << "Item has been found, bitch. Details are as follows:\n" << endl;
            cout << "Brand name: " << info->brandName << endl;
            cout << "Item name: " << info->itemName << endl;
            cout << "Item quantity: " << info->quantity << endl;
            cout << "Expiry date: " << info->date.getDate() << endl;
        }
    }
    else if(choice==4) {
        int year, month, day;
        cout << "\n\nEnter Expiry Date (Day/Month/Year): ";
        cin >> day >> month >> year;
        Date date(day, month, year);
        MergeSort(&top, 7);
        if(binSearch(top, date) == NULL)
            cout << "Item with name " << input << " not found." << endl;
        else {
            Inventory* info = binSearch(top, date);

            cout << "Item has been found, bitch. Details are as follows:\n" << endl;
            cout << "Brand name: " << info->brandName << endl;
            cout << "Item name: " << info->itemName << endl;
            cout << "Item quantity: " << info->quantity << endl;
            cout << "Expiry date: " << info->date.getDate() << endl;
        }
    }

    /*{
        while(getline(inputFile, brandName, '\t')){
            defaultCounter++;
            getline(inputFile, itemName, '\t');
            inputFile >> quantity;
            if(stoi(input) == quantity)
            {
                selected = defaultCounter;
                found = true;
                break;
            }
        }
    }
    else
    {   
        while(getline(inputFile, brandName, '\t')){
            defaultCounter++;
            if(strLower(input) == strLower(brandName))
            {
                getline(inputFile, itemName, '\t');
                inputFile >> quantity;
                found = true;
                break;
            }
            getline(inputFile, itemName, '\t');
            if(strLower(input) == strLower(itemName))
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
        cout << "Date: "
        cout << endl << endl << endl << "Please select which property to edit";
    }
    else cout << "Item not found." << endl;*/


    //To-dos:
    //Implement editing functions
}


#endif
