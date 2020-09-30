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

    Date(int d, int m, int y)
    {
        this->day = d;
        this->month = m;
        this->year = y;
    }
    Date (Date& copyD)
    {
        this->day = copyD.getDay();
        this->month = copyD.getMonth();
        this->year = copyD.getYear();
    }

    void setMonth(int month)
    {
        this->month = month; // implement during call check if month > 12 <1
    }

    void setMonth(string strMonth)
    {
        transform(strMonth.begin(), strMonth.end(), strMonth.begin(), [](unsigned char c){return tolower(c);});
    }

    void setYear(int year)
    {
        this->year = year;
    }

    void setDay(int day)
    {
        this->day = day;
    }
    int getDay() {return this->day;}
    int getMonth() {return this->month;}
    int getYear() {return this->year;}
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
        out << D.day << "/" << D.month << "/" << D.year;
        return out;
    }

    friend istream& operator>>(istream& in, Date& D)
    {
        in >> D.day >> D.month >> D.year;
        return in;
    }
};
#endif

