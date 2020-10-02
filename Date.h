#include <algorithm>
#include <iostream>
#include <string>
#ifndef DATE
#define DATE
using namespace std;

class Date
{
    int day;
    int month;
    int year;

public:
    Date()
    {
        this->day = 1;
        this->month = 1;
        this->year = 2012;
    }

    Date(int day, int month, int year)
    {
        this->year = year; //year initialisation
        this->month = month;
        this->day = day;
    }

    Date (Date& copyD)
    {
        this->day = copyD.getDay();
        this->month = copyD.getMonth();
        this->year = copyD.getYear();
    }

    void setMonth(int month)
    {
       this->month = month;
    }

    void setYear(int year)
    {
        this->year = year;
    }

    void setDay(int day)
    {
        this->day = day;
    }



    int getDay() {return day;}
    int getMonth() {return month;}
    int getYear() {return year;}

    string getDate()
    {
        string d = to_string(getDay());
        string mon = to_string(getMonth());
        string yr = to_string(getYear());
        string date = d + "/" + mon + "/" + yr;
        return date;
    }

    friend ostream& operator<<(ostream& out, const Date& D)
    {
        out << D.day << '\t' << D.month << '\t' << D.year;
        return out;
    }

    friend istream& operator>>(istream& in, Date& D)
    {
        in >> D.day >> D.month >> D.year;
        return in;
    }
};



#endif

