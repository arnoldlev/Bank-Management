// Arnold Lev
// CSIS 137 (Online)
// Final Project

#include "Date.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

Date::Date(const string& parse) {
    parseDate(parse);
}

Date::Date(int mn, int dy, int yr) {
    setDate(mn, dy, yr);
}

Date& Date::setDate(int mn, int dy, int yr) {
    setMonth(mn).setDay(dy).setYear(yr);
    return *this;
}

Date& Date::setMonth(int month) {
    if (month > 0 && month <= 12) {
        this->month = month;
    } else {
        this->month = -1; // For input validation 
    }
    return *this;
}

Date& Date::setDay(int day) {
    this->day = checkDay(day);
    return *this;
}

Date& Date::setYear(int year) {
    this->year = checkYear(year);
    return *this;
}

int Date::getMonth() const {
    return month;
}

int Date::getDay() const {
    return day;
}

int Date::getYear() const {
    return year;
}

string Date::toString() const {
    string worded = to_string(getMonth()) + "/" + to_string(getDay()) + "/" + to_string(getYear());
    return worded;
}

Date Date::addMonth(int months) {
    int newMonth = getMonth() + months;
    Date date = Date::getTodayDate();
    if (newMonth <= 12) {
        date.setMonth(newMonth);
    } else {
        newMonth -= 12;
        date.setMonth(newMonth).setYear(getYear() + 1);
    }
    return date;
}

bool Date::parseDate(const string& line) {
    vector<int> tokens;
    stringstream msg(line);
    string holder;
    while (getline(msg, holder, '/')) {
        tokens.push_back(stoi(holder));
    }

    if (tokens.size() == 3) {
        setMonth(tokens[0]).setDay(tokens[1]).setYear(tokens[2]);
        return true;
    } else {
        return false;
    }

    tokens.clear();
}

Date Date::getTodayDate() {
    time_t rawtime;
    time(&rawtime);
    struct tm timeinfo;
    localtime_s(&timeinfo, &rawtime); // Got this from cplusplus.com and stackoverflow. Using localtime was deprecated so using localtime_s instead

    Date today(timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_year + 1900);
    return today;
}

bool Date::operator==(const Date& date2) const {
    if (month == date2.month && day == date2.day && year == date2.year) {
        return true;
    }
    return false;
}

bool Date::operator!=(const Date& date2) const {
    return !(*this == date2);
}

bool Date::operator<(const Date& date2) const {
    if (year < date2.year) {
        return true;
    }
    else if (year == date2.year && month < date2.month) {
        return true;
    }
    else if (month == date2.month && day < date2.day) {
        return true;
    }
    return false;
}

bool Date::operator<=(const Date& date2) const {
    if (*this < date2) {
        return true;
    }
    else if (*this == date2) {
        return true;
    }
    return false;
}

bool Date::operator>(const Date& date2) const {
    if (year > date2.year) {
        return true;
    }
    else if (year == date2.year && month > date2.month) {
        return true;
    }
    else if (month == date2.month && day > date2.day) {
        return true;
    }
    return false;
}

bool Date::operator>=(const Date& date2) const {
    if (*this > date2) {
        return true;
    }
    else if (*this == date2) {
        return true;
    }
    return false;
}

// Input Validation Function
bool Date::isInvalid() const {
    return month == -1 || day == -1 || year == -1;
}

int Date::checkYear(int testYear) const {
    int digits = 0;
    int test = testYear;
    while (test != 0) {
        test /= 10;
        digits++;
    }

    if (digits == 4 && testYear > 0) {
        return testYear;
    }
    else {
        return -1; // For input validation
    }
}

int Date::checkDay(int testDay) const {
    static const int daysPerMonth[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    if (testDay > 0 && testDay <= daysPerMonth[month]) {
        return testDay;
    }
    if (month == 2 && testDay == 29 && (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))) {
        return testDay;
    }
    return -1; // For input validation
}

ostream& operator<<(ostream& out, const Date& date) {
    out << date.month << "/" << date.day << "/" << date.year;
    return out;
}

istream& operator>>(istream& in, Date& date) {
    int month, day, year;
    in >> setfill('0') >> setw(2) >> month;
    cin.ignore();
    in >> setfill('0') >> setw(2) >> day;
    cin.ignore();
    in >> setw(4) >> year; 

    while (in.fail()) {
        cout << "\t\t\t(!) Error: You entered a bad date! Try again: (MM/DD/YYYY)" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        in >> setfill('0') >> setw(2) >> month;
        cin.ignore();
        in >> setfill('0') >> setw(2) >> day;
        cin.ignore();
        in >> setw(4) >> year;
    }

    date.setDate(month, day, year);

    while (date.isInvalid()) {
        cout << "\t\t\t(!) Error: You entered a bad date! Try again: (MM/DD/YYYY)" << endl;
        in >> date;
    }
    return in;
}