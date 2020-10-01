#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>
#include <time.h>
#include <cstdlib>
#include "Date.h"
#include "center_helper.h"
#ifndef INVENTORY
#define INVENTORY
using namespace std;

namespace InventoryStack{
    struct Inventory
    {
        string brandName;
        string itemName;
        int quantity;
        Date date;
        struct Inventory* next;
    };

    struct Inventory* top;

    void push(string brandName, string itemName, int quantity, Date expiryDate)
    {
        struct Inventory* temp;
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
        struct Inventory* temp;

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
        system("CLS");
        int counter = 0;
        Inventory* temp;

        if(isEmpty())
            cout << "Nothing to show" << endl;
        else {
            temp = top;
            cout << setw(5)<<centered("No.") << setw(12)<<centered("Brand") << setw(20) << centered("Item") << setw(10) << centered("Quantity") << setw(20) << centered("Expiry Date") << '\n';
            cout << "______________________________________________________________\n";
            while(temp!=NULL)
            {
                counter++;
                cout << endl;
                cout << setw(2)<<counter << ")" << setw(15) << centered((string)temp->brandName) << setw(20) << centered((string)temp->itemName) << setw(5) << temp->quantity << setw(28) << centered((string)temp->date.getDate()) << endl;
                temp = temp->next;
            }
        }
    }
    void showInventoryWithExpiryDate()
    {
        system("CLS");
        time_t rawtime;
        struct tm* timeinfo;
        char d[10], m[10], y[10];
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(d,10,"%d",timeinfo);
        strftime(m,10,"%m",timeinfo);
        strftime(y,10,"%Y",timeinfo);
        int currentDay = atoi(d);
        int currentMonth = atoi(m);
        int currentYear = atoi(y);
        int counter = 0;
        string status = "";
        struct Inventory* temp;

        if(isEmpty())
            cout << "Nothing to show" << endl;
        else {
            temp = top;
            cout << setw(5)<<centered("No.") << setw(12)<<centered("Brand") << setw(20) << centered("Item") << setw(10) << centered("Quantity") << setw(20) << centered("Expiry Date") << '\n';
            cout << "______________________________________________________________\n";
            while(temp!=NULL)
            {
                if (temp->date.getYear() == currentYear && temp->date.getMonth() == currentMonth)
                {
                    if (temp->date.getDay() == currentDay)
                    {
                        status = "(Expired)";
                    }
                    else if (temp->date.getDay() < currentDay)
                    {
                        status = "(Expiring Soon)";
                    }
                    else
                    {
                        status = "(Expired)";
                    }
                }
                else if (temp->date.getYear() < currentYear)
                {
                    status = "(Expired)";
                }
                counter++;

                cout << endl;
                cout << setw(2)<<counter << ")" << setw(15) << centered((string)temp->brandName) << setw(20) << centered((string)temp->itemName) << setw(5) << temp->quantity << setw(28) << centered((string)temp->date.getDate()) << "  " <<status<< endl;
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
        cin.ignore();
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
        std::system("CLS");  //use ("cls") on Windows
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
}

#endif
