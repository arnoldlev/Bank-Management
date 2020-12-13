// Arnold Lev
// CSIS 137 (Online)
// Final Project

#ifndef DATE_H
#define DATE_H
#include <iostream>
using namespace std;

class Date {

    friend istream& operator>>(istream&, Date&);
    friend ostream& operator<<(ostream&, const Date&);

    private:
        int month;
        int day;
        int year;
        int checkDay(int) const;
        int checkYear(int) const;
    public:
        Date(const string&);
        Date(int = 1, int = 1, int = 1990);

        Date& setMonth(int);
        Date& setDay(int);
        Date& setYear(int);
        Date& setDate(int, int, int);

        static Date getTodayDate(); // NEW
        int getMonth() const;
        int getDay() const;
        int getYear() const;
        string toString() const;
        
        Date addMonth(int);
        bool parseDate(const string&);

        bool operator>(const Date&) const;
        bool operator<(const Date&) const;
        bool operator>=(const Date&) const;
        bool operator<=(const Date&) const;
        bool operator==(const Date&) const;
        bool operator!=(const Date&) const;

        bool isInvalid() const;

};

#endif