#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cctype>
#include "Date.h"
#include "InventoryStack.h"
#ifndef MERGESORT
#define MERGESORT

using namespace std;

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
    else if(scenario==7) {      //Sorting scenario 7 (Ascending)
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

#endif