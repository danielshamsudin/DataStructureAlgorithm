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

        if(month > 0 && month < 13)
            this->month = month; //month initialisation
        else cout << "Invalid month!" << endl;
        
        if(month==2) {
            if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))  {
                if(day <= 29 && day > 0)
                    this->day = day; //day initialisation for leap year
                else
                    cout << "Please enter a valid day range for the February!" << endl;
            }
            else if (day <=28 && day > 0)
                this->day = day; //day initialisation for February
            else
                cout << "Please enter a valid day range for the February!" << endl;

        }
        else if(month==3 || month==5 || month==7 || month==8 || month==10 || month==12) {
            if(day <= 31 && day > 0)
                this->day = day; //day initialisation for months with 31 days
            else
                cout << "Please enter a valid day range for the month!" << endl;
        }
        else
            if(day <= 30 && day > 0)
                this->day = day; //day initialisation for months with 30 days
            else
                cout << "Please enter a valid day range for the month!" << endl;
    }

    Date (Date& copyD)
    {
        this->day = copyD.getDay();
        this->month = copyD.getMonth();
        this->year = copyD.getYear();
    }

    void setMonth(int month)
    {
        if(month > 0 && month < 13)
            this->month = month;
        else cout << "Invalid month!" << endl; 
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
        if(month==2) {
            if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))  {
                if(day <= 29 && day > 0)
                    this->day = day;
                else
                    cout << "Please enter a valid day range for the February!" << endl;
            }
            else if (day <=28 && day > 0)
                this->day = day;
            else
                cout << "Please enter a valid day range for the February!" << endl;

        }
        else if(month==3 || month==5 || month==7 || month==8 || month==10 || month==12) {
            if(day <= 31 && day > 0)
                this->day = day;
            else
                cout << "Please enter a valid day range for the month!" << endl;
        }
        else
            if(day <= 30 && day > 0)
                this->day = day;
            else
                cout << "Please enter a valid day range for the month!" << endl;
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

