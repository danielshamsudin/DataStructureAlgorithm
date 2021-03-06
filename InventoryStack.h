#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <cstdlib>
#include "Date.h"
#include "center_helper.h"
//#include <unistd.h>
#ifndef INVENTORY_STACK
#define INVENTORY_STACK

using namespace std;

namespace InventoryStack
{
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
        else
        {
            temp->brandName = brandName;
            temp->itemName = itemName;
            temp->quantity = quantity;
            temp->date = expiryDate;
            temp->next = top;
            top = temp;
        }
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
        in >> ws;
        while(getline(in,brandName, '\t'))
        {
            getline(in, itemName, '\t');
            in >> quantity;
            in >> temp;
            push(brandName, itemName, quantity, temp);
            in.get();
        }
        in.close();
    }

    void emptyStack()
    {
        while(!isEmpty())
        {
            pop();
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
        string status = "|";
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
                        status = "|(Expired)";
                    }
                    else if (temp->date.getDay() > currentDay)
                    {
                        status = "|(Expiring Soon)";
                    }
                    else
                    {
                        status = "|(Expired)";
                    }
                }
                else if (temp->date.getYear() < currentYear )
                {
                    status = "|(Expired)";
                }
                else if (temp->date.getYear() == currentYear && temp->date.getMonth() < currentMonth)
                    status = "|(Expired)";
                else
                    status = "|";

                counter++;

                cout << endl;
                cout << setw(2)<<counter << ")" << setw(15) << centered((string)temp->brandName) << setw(20) << centered((string)temp->itemName) << setw(5) << temp->quantity << setw(28) << centered((string)temp->date.getDate()) <<status<< endl;
                temp = temp->next;
            }
            cout << "______________________________________________________________\n";
        }
    }

    int int_range_validation (int a, int b, const string& msg)
    {
        int i;
        bool showMsg =  false;

        do
        {
            if (showMsg)
            {
                cout << msg;
            }
            else
            {
                showMsg = true;
            }
            cin >> i;
            while(cin.fail())
            {
                cout << "Entered choice is not an integer!\n";
                cin.clear();
                cin.ignore(256,'\n');
                cout << "Please enter menu choice: ";
                cin >> i;
            }  
        }while( i < a || i > b);

        return i;
    }

    void addItem()
    {
        string brandName,itemName;
        int quantity, day, month, year;
        cout << "Enter brand, item name, quantity, and expiry date: \n";
        cout << "Brand Name: "; //add cin.ignore() if fails
        cin.ignore();
        getline(cin, brandName);
        cout << "Item Name: ";
        getline(cin,itemName);
        cout << "Quantity: ";
        cin >> quantity;
        cout << "Date: \n";
        cout << "Please enter a year:";
        year = int_range_validation(1900,3000,"Please enter a valid year (1900-3000) :");
        cout << "Please enter a month:";
        month = int_range_validation(1,12,"Please enter a valid month (1-12)!:");
        cout << "Please enter day:";
        if (month == 2)
        {
            if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
            {
                day = int_range_validation(1,29, "Error, Please enter valid day! (1-29):");
            }
            else
            {
                day = int_range_validation(1,28,"Error, Please enter valid day! (1-28):");
            }
        }
        else if (month==3 || month==5 || month==7 || month==8 || month==10 || month==12)
        {
            day = int_range_validation(1,31,"Error, Please enter valid day! (1-31):");
        }
        else
        {
            day = int_range_validation(1,30,"Error, Please enter valid day! (1-30):");
        }


        Date dte(day, month, year);
        push(brandName, itemName, quantity, dte);
        ofstream out("inventory.dat", ios::app);
        out << brandName << '\t' << itemName << '\t' << quantity << '\t' << dte << '\n';
        cout << "Item has been added successfully. Press any key to continue." << endl;
        out.close();
        cin.get();
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
        system("CLS");  //use ("cls") on Windows
        int entry;
        showInventoryWithExpiryDate();
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

    void removeItem()
    {
        const char *fileName = "inventory.dat";
        int line, totalLine=0, defaultCounter = 1, quantity, d, m, y;
        cout << "Select the item that you wish to remove (by number): ";
        cin >> line;
        ifstream inputFile(fileName);
        ofstream outputTempFile("temp.dat", ofstream::out);
        string brandName, itemName, expire, dummy;
        Date date;
        char c;

        inputFile >> ws;
        while(!inputFile.eof())
        {
            getline(inputFile,dummy,'\n');
            if(!dummy.size())
                continue;
            totalLine++;
        }

        inputFile.close();
        inputFile.open(fileName);
        inputFile >> ws;
        while (inputFile.get(c)) {
            if (c == '\n')
                defaultCounter++;
            if (defaultCounter != (totalLine - line + 1))
                outputTempFile << c;
        }

        inputFile.close();
        outputTempFile.close();

        remove(fileName);
        rename("temp.dat", fileName);
        cout << "Item " << line << " has been removed." << endl;
        emptyStack();
    }

    Inventory* seqSearch(Inventory* top, int qty) //overloaded sequential search fn for quantity
    {
        Inventory* temp = top;

        while(temp!=NULL)
        {

            if(temp->quantity==qty)
                return temp;

            temp = temp->next;
        }

        return NULL;
    }

    Inventory* seqSearch(Inventory* top, string input, int choice) //overloaded sequential search fn for string-based data
    {
        Inventory* temp = top;

        while(temp!=NULL)
        {
            if(choice==1) {
                if(temp->brandName==input)
                    return temp;
            }
            else if(choice==2) {
                if(temp->itemName==input)
                    return temp;
            }
            temp = temp->next;
        }

        return NULL;
    }

    Inventory* seqSearch(Inventory* head, Date d) //overloaded sequential search fn for date-based data
    {
        Inventory* temp = top;

        while(temp!=NULL)
        {
            if(temp->date.getYear()==d.getYear()) {
                if(temp->date.getMonth()==d.getMonth()){
                    if(temp->date.getDay()==d.getDay())
                        return temp;
                }
            }
            temp = temp->next;
        }
        return NULL;
    }



    void editItem()
    {
        const char *filename = "inventory.dat";
        int defaultCounter = 1, selected, quantity, choice;
        bool found = false;
        string input, brandName, itemName;
        Inventory* info;


        cout << "Search the item that you wish to edit: \n" << endl;
        cout << "1.) Search by Brand name: " << endl;
        cout << "2.) Search by Item name: " << endl;
        cout << "3.) Search by Item quantity: " << endl;
        cout << "4.) Search by expiry date: \n" << endl << endl;
        cout << "Choice: ";

        cin >> choice;
        system("CLS");
        if(choice==1) {
            cout << "\n\nEnter Brand Name: ";
            cin.ignore();
            getline(cin, input);;
            if(seqSearch(top, input, choice) == NULL)
                cout << "Item with brand name " << input << " not found." << endl;
            else {
                info = seqSearch(top, input, choice);

                cout << "Item has been found. Details are as follows:" << endl;
                cout << "----------------------------------------------\n";
                cout << "Brand name: " << info->brandName << endl;
                cout << "Item name: " << info->itemName << endl;
                cout << "Item quantity: " << info->quantity << endl;
                cout << "Expiry date: " << info->date.getDate() << endl;
                cout << "----------------------------------------------\n";
                found = true;
            }
        }
        else if(choice==2) {
            cout << "\n\nEnter Item Name: ";
            cin.ignore();
            getline(cin, input);
            if(seqSearch(top, input, choice) == NULL)
                cout << "Item with name " << input << " not found." << endl;
            else {
                info = seqSearch(top, input, choice);

                cout << "Item has been found. Details are as follows:" << endl;
                cout << "----------------------------------------------\n";
                cout << "Brand name: " << info->brandName << endl;
                cout << "Item name: " << info->itemName << endl;
                cout << "Item quantity: " << info->quantity << endl;
                cout << "Expiry date: " << info->date.getDate() << endl;
                cout << "----------------------------------------------\n";
                found = true;
            }
        }
        else if(choice==3) {
            cout << "\n\nEnter Item Quantity: ";
            cin >> input;
            if(seqSearch(top, stoi(input)) == NULL)
                cout << "Item not found." << endl;
            else {
                info = seqSearch(top, stoi(input));

                cout << "Item has been found. Details are as follows:" << endl;
                cout << "----------------------------------------------\n";
                cout << "Brand name: " << info->brandName << endl;
                cout << "Item name: " << info->itemName << endl;
                cout << "Item quantity: " << info->quantity << endl;
                cout << "Expiry date: " << info->date.getDate() << endl;
                cout << "----------------------------------------------\n";
                found = true;
            }
        }
        else if(choice==4) {
            int year, month, day;
            cout << "\n\nEnter Expiry Date (Day):  ";
            cin >> day;
            cout << "\nEnter Expiry Date (Month):  ";
            cin >> month;
            cout << "\nEnter Expiry Date (Year):  ";
            cin >> year;

            Date date(day, month, year);
            system("CLS");

            if(seqSearch(top, date) == NULL)
                cout << "Item with name " << input << " not found." << endl;
            else {
                info = seqSearch(top, date);

                cout << "Item has been found. Details are as follows:" << endl;
                cout << "----------------------------------------------\n";
                cout << "Brand name: " << info->brandName << endl;
                cout << "Item name: " << info->itemName << endl;
                cout << "Item quantity: " << info->quantity << endl;
                cout << "Expiry date: " << info->date.getDate() << endl;
                cout << "----------------------------------------------\n";
                cout << endl;
                found =true;
            }
        }

        if(found)
        {
            cout << "\n\n";
            cout << "Select the property to edit: " << endl << endl;
            cout << "1.) Brand name: " << endl;
            cout << "2.) Item name: " << endl;
            cout << "3.) Item quantity: " << endl;
            cout << "4.) Expiry date: " << endl;

            cin >> choice;
            if(choice==1) {
                cout << "\n\nEnter New Brand Name: ";
                cin.ignore();
                getline(cin, input);
                info->brandName = input;
            }
            if(choice==2) {
                cout << "\n\nEnter New Item Name: ";
                cin.ignore();
                getline(cin, input);
                info->itemName = input;
            }
            else if(choice==3) {
                cout << "\n\nEnter Item Quantity: ";
                cin >> input;
                info->quantity = stoi(input);
            }
            else if(choice==4) {
                int year, month, day;
                cout << "\n\nEnter New Expiry Date: \n";
                cout << "Year:";
                year = int_range_validation(1900,3000,"Please enter a valid year (1900-3000) :");
                cout << "Month:";
                month = int_range_validation(1,12,"Please enter a valid month (1-12)!:");
                cout << "Day:";
                if (month == 2)
                {
                    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
                    {
                        day = int_range_validation(1,29, "Error, Please enter valid day! (1-29):");
                    }
                    else
                    {
                        day = int_range_validation(1,28,"Error, Please enter valid day! (1-28):");
                    }
                }
                else if (month==3 || month==5 || month==7 || month==8 || month==10 || month==12)
                {
                    day = int_range_validation(1,31,"Error, Please enter valid day! (1-31):");
                }
                else
                {
                    day = int_range_validation(1,30,"Error, Please enter valid day! (1-30):");
                }
                Date newdate(day, month, year);
                info->date = newdate;
            }

            Inventory* temp = top;
            ofstream out(filename, ios::trunc);
            while(temp!=NULL)
            {
                out << temp->brandName << '\t' << temp->itemName << '\t' <<  temp->quantity << '\t' << temp->date << '\n';
                temp = temp->next;

            }
            out.close();
        }
    }
}

#endif
